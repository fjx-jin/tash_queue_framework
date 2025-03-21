#include <functional>
struct Pose2D {
  double x;
  double y;
  double theta;
};

enum NavigationStatus {};
enum ErrorCode { not_in_map = -1 };

namespace NavigationInterface {
// 系统控制接口
void init();
int start(int& id); // 开始工作 正数时返回任务id 负数时返回错误状态
int pause(int &);
int resume(int &);
int cancle(int &);

// 回调注册接口
// using MapCallback = std::function<void(const GridMap &)>;
using PoseCallback = std::function<Pose2D()>;
// using PathCallback = std::function<void(const Path &)>;
using VehicleControlCallback = std::function<void(const double &, const double &)>;
// using NavigationStatusCallback = std::function<void(NavigationStatus)>;
using GetNextPointCallback = std::function<void(Pose2D &)>;
using InitPlanCallback = std::function<void(int&)>;

// void registerMapUpdateCallback(MapCallback cb);
void registerPoseUpdateCallback(PoseCallback cb);
// void registerPathUpdateCallback(PathCallback cb);
// void registerEmergencyStopCallback(std::function<void()> cb);
void registerVehicleControlCallback(VehicleControlCallback cb); // 轮速控制
// void registerNavigationStatusCallback(NavigationStatusCallback cb); // 导航状态
void registerGetNextPointCallback(GetNextPointCallback cb); // 获取下一个点
void registerInitPlanCallback(InitPlanCallback cb); //计算路径
}; // namespace NavigationInterface

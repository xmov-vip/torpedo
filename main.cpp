
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 地球半径
const double EARTH_RADIUS = 6371.0;

// 角度转弧度
double to_radian(double angle) {
  return angle * M_PI / 180.0;
}

// 弧度转角度
double to_angle(double radian) {
  return radian * 180.0 / M_PI;
}

// 计算两点之间的距离
double distance(double lat1, double lon1, double lat2, double lon2) {
  double rad_lat1 = to_radian(lat1);
  double rad_lat2 = to_radian(lat2);
  double a = rad_lat1 - rad_lat2;
  double b = to_radian(lon1) - to_radian(lon2);
  double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(rad_lat1) * cos(rad_lat2) * pow(sin(b / 2), 2)));
  s *= EARTH_RADIUS;
  return s;
}

// WCS坐标转GPS坐标
void wcs_to_gps(double wcs_x, double wcs_y, double wcs_z, double& lat, double& lon, double& alt) {
  // TODO: WCS坐标转GPS坐标的具体算法实现
}

// GPS坐标转WCS坐标
void gps_to_wcs(double lat, double lon, double alt, double& wcs_x, double& wcs_y, double& wcs_z) {
  // TODO: GPS坐标转WCS坐标的具体算法实现
}

// 验证WCS坐标和GPS坐标转换的精度
void verify_conversion(double wcs_x, double wcs_y, double wcs_z, double gps_lat, double gps_lon, double gps_alt) {
  // WCS坐标转GPS坐标
  double calc_gps_lat, calc_gps_lon, calc_gps_alt;
  wcs_to_gps(wcs_x, wcs_y, wcs_z, calc_gps_lat, calc_gps_lon, calc_gps_alt);

  // GPS坐标转WCS坐标
  double calc_wcs_x, calc_wcs_y, calc_wcs_z;
  gps_to_wcs(gps_lat, gps_lon, gps_alt, calc_wcs_x, calc_wcs_y, calc_wcs_z);

  // 计算误差
  double lat_error = fabs(calc_gps_lat - gps_lat);
  double lon_error = fabs(calc_gps_lon - gps_lon);
  double alt_error = fabs(calc_gps_alt - gps_alt);
  double wcs_x_error = fabs(calc_wcs_x - wcs_x);
  double wcs_y_error = fabs(calc_wcs_y - wcs_y);
  double wcs_z_error = fabs(calc_wcs_z - wcs_z);

  // 输出结果
  cout << fixed << setprecision(8);
  cout << "WCS坐标转GPS坐标：" << endl;
  cout << "计算结果：(" << calc_gps_lat << ", " << calc_gps_lon << ", " << calc_gps_alt << ")" << endl;
  cout << "真实结果：(" << gps_lat << ", " << gps_lon << ", " << gps_alt << ")" << endl;
  cout << "误差：(" << lat_error << ", " << lon_error << ", " << alt_error << ")" << endl;

  cout << "GPS坐标转WCS坐标：" << endl;
  cout << "计算结果：(" << calc_wcs_x << ", " << calc_wcs_y << ", " << calc_wcs_z << ")" << endl;
  cout << "真实结果：(" << wcs_x << ", " << wcs_y << ", " << wcs_z << ")" << endl;
  cout << "误差：(" << wcs_x_error << ", " << wcs_y_error << ", " << wcs_z_error << ")" << endl;

  // 判断是否通过验证
  double max_error = 0.00001; // 最大误差
  bool pass_verification = true;
  if (lat_error > max_error || lon_error > max_error || alt_error > max_error ||
      wcs_x_error > max_error || wcs_y_error > max_error || wcs_z_error > max_error) {
    pass_verification = false;
  }

  if (pass_verification) {
    cout << "WCS坐标和GPS坐标转换精度验证通过！" << endl;
  } else {
    cout << "WCS坐标和GPS坐标转换精度验证未通过！" << endl;
  }
}

int main() {
  // 验证示例：将WCS坐标(100, 200, 300)转换为GPS坐标(30.0, 120.0, 100.0)，然后再转换回WCS坐标
  double wcs_x = 100.0;
  double wcs_y = 200.0;
  double wcs_z = 300.0;
  double gps_lat = 30.0;
  double gps_lon = 120.0;
  double gps_alt = 100.0;

  verify_conversion(wcs_x, wcs_y, wcs_z, gps_lat, gps_lon, gps_alt);

  return 0;
}

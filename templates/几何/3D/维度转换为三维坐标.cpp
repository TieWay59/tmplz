// 经纬度转换为球坐标
double torad(double deg)
{
    return deg/180*acos(-1);
}
void get_coordinate(double R,double lat,double lng,double &x,double &y,double &z)
{
    lat = torad(lat);
    lng = torad(lng);
    x = R*cos(lat)*cos(lng);
    y = R*cos(lat)*sin(lng);
    z = R*sin(lat);
}

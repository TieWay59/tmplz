void To_string_base2(LL n,string &s){
  while(n > 0){
    if(n&1)
      s += "1";
    else
      s += "0";
    n >>= 1;
  };
  reverse(s.begin(),s.end());
}
// nn是要转化的数，ss是string，n转化成多少位2进制
void To_string_base2_n(LL nn,string &ss,int n){
    ss.clear();
    To_string_base2(nn,ss);
      while((int)ss.size() < n)
        ss = "0"+ss;
}

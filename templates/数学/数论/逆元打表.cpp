 int inv[10000];
    int p;
    cin>>p;
    inv[1] = 1;
    for(int i = 2;i < p; ++i)
    {
        inv[i] = (p - p/i*inv[p%i]%p)%p;
    }
    for(int i = 1;i < p; ++i)
        cout<<inv[i]<<" ";
    cout<<endl;
    for(int i = 1;i < p; ++i)
        cout<<i * inv[i] % p<<" ";

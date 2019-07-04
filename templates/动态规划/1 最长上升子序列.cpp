//最长上升子序列 The longest increasing sequence

template  <class It>
int n_lisLength(It begin,It end)
{
    typedef typename iterator_traits<It>::value_type T;
    T inf = 1<<30;
    vector<T> best(end-begin,inf);
    for(It i = begin; i != end; ++i)
        *lower_bound(best.begin(),best.end(),*i) = *i;
    return lower_bound(best.begin(),best.end(),inf) - best.begin();

}


    clock_t start,end;
    start = clock();
    end = clock();
    dur = double(end - start);
    printf("Use Time: %f\n",(dur/CLOCKS_PER_SEC));

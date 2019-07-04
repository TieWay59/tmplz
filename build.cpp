#include <iostream>
#include <string>
#include <windows.h>

int find_path(const char *, const int &);

char save_path[MAX_PATH] = {0};//结果输出路径;
char szPath[MAX_PATH] = {0};
char result[MAX_PATH] = {0};
char fHead[5000] = {0};
char fTail[500] = {0};
FILE *pf_path_file;

//write function
void writeSection(const int &level, const char *secName) {
    switch (level) {
        case 1:
            fprintf(pf_path_file, "\\section{%s}\n", secName);
            break;
        case 2:
            fprintf(pf_path_file, "\\subsection{%s}\n", secName);
            break;
        case 3:
            fprintf(pf_path_file, "\\subsubsection{%s}\n", secName);
            break;
        default:
            fprintf(pf_path_file, "\\subsubsection{%s !Error Level!}\n", secName);
            break;
    }
}

void reWritePath(char *tPath) {
    for (int i = 0; tPath[i] != 0; ++i) {
        if (tPath[i] == '\\')tPath[i] = '/';
    }
}

void writeMintedPath(const char *lang, const char *tPath) {
    std::string language = lang;
    if (language == "java") {
        fprintf(pf_path_file, "\\inputminted[breaklines]{java}{\"%s\"}\n", tPath);
        //如果路径里面有空格，那么要给路径加上引号，否则控制台找不到。
    } else if (language == "py") {
        fprintf(pf_path_file, "\\inputminted[breaklines]{python}{\"%s\"}\n", tPath);
    } else {
        fprintf(pf_path_file, "\\inputminted[breaklines]{c++}{\"%s\"}\n", tPath);
    }
}


int find_path_save_file(const char *lp_path, const char *out_file_name) {
    pf_path_file = fopen(out_file_name, "w");
    fprintf(pf_path_file, "%s\n", fHead);
    int cnt = find_path(lp_path, 1);
    fprintf(pf_path_file, "%s\n", fTail);
    fclose(pf_path_file);
    return cnt;
}

void str_tok(char *str) //分离文件目录
{
    char *p = NULL;
    char delims[] = "\\";
    p = strtok(str, delims);
    while (p != NULL) {
        strcpy(result, p);
        p = strtok(NULL, delims);
    };
}

void str_extension(char *str) //分离文件扩展名;
{
    char *p = NULL;
    char delims[] = ".";
    p = strtok(str, delims);
    while (p != NULL) {
        strcpy(result, p);
        p = strtok(NULL, delims);
    };
}

int find_path(const char *lp_path, const int &level)// 遍历搜索目录
{
    static int cnt = 0;
    HANDLE hFile;

    WIN32_FIND_DATAA wfd; //数据结构;
    char sz_path[MAX_PATH] = {0};
    char buf[MAX_PATH * 2] = {0};
    char fileName[MAX_PATH] = {0};
    char temp[MAX_PATH] = {0};//临时数组;
    char parseFileName[MAX_PATH] = {0};

    strcpy(sz_path, lp_path);
    strcat(sz_path, "\\*.*"); //匹配任何文件包括文件夹目录;
    hFile = FindFirstFile(sz_path, &wfd);

    if (hFile != INVALID_HANDLE_VALUE) {
        do {
            if (wfd.cFileName[0] == '.') //如果是.或..则过滤;
                continue;
            else if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //如果是目录则递归;
            {
                strcpy(sz_path, lp_path);
                strcat(sz_path, "\\");
                strcat(sz_path, wfd.cFileName);    //拼接目录全路径名;

                writeSection(level, wfd.cFileName);        //写标题

                find_path(sz_path, level + 1);            //调用递归;
            } else {
                strcpy(parseFileName, wfd.cFileName);
                str_extension(parseFileName);//分离文件的扩展名;
                //过滤规则,只接受.c,.py,.cpp,.java文件，这里可以修改规则;
                if ((!strcmp(result, "c")) ||
                    (!strcmp(result, "cc")) ||
                    (!strcmp(result, "py")) ||
                    (!strcmp(result, "cpp")) ||
                    (!strcmp(result, "java"))
                        ) {
                    strcpy(fileName, lp_path);//合成文件名全路径
                    strcat(fileName, "\\");
                    strcat(fileName, wfd.cFileName);/* 例："c:\dir\test\1.pgm" */

                    writeSection(level, wfd.cFileName); //写标题
                    reWritePath(fileName);
                    printf("%s\n", fileName);

//                    strcpy(temp, lp_path);
//                    str_tok(temp); //获取目录

//                    sprintf(buf, "%s;%s", fileName, result);
//                    fprintf(pf_path_file, "%s\n", buf);
                    //fprintf(pf_path_file, "%s\n", fileName);
                    writeMintedPath(result, fileName);
                    ++cnt;
                }

            }
        } while (FindNextFile(hFile, &wfd));
    }
    return cnt;
}

int main() {
    std::string signal;
    printf("本程序版本 v 0.5 注意：\n");
    printf("文件层次不要超过三层，更细的划分方式还没实现兼容。\n");
    printf("由于未知的原因，路径里出现某些符号会不合法。\n");
    printf("请确认以上几点后，输入start开始构建。\n");


    while (std::cin >> signal) {
        if (signal == "start") {
            GetCurrentDirectory(MAX_PATH, szPath); //当前目录

            strcpy(save_path, szPath);
            strcat(save_path, "\\buildUtils\\head.txt");
            pf_path_file = fopen(save_path, "r");
            fread(fHead, 2000, 1, pf_path_file);//不一定是要2000，根据自己文件的情况修改大小
            fclose(pf_path_file);

            strcpy(save_path, szPath);
            strcat(save_path, "\\buildUtils\\tail.txt");
            pf_path_file = fopen(save_path, "r");
            fread(fTail, 2000, 1, pf_path_file);
            fclose(pf_path_file);

            strcpy(save_path, szPath);//结果result.txt放在当前目录中;
            strcat(save_path, "\\buildUtils\\LaTeX\\context.tex");


            printf("%s\n", save_path);
            printf("%s\n", fHead);
            printf("%s\n", fTail);

            strcat(szPath, "\\templates");
            int num = find_path_save_file(szPath, save_path);
            printf("Number of indexed code file(s):%d\n", num);
        } else {
            printf("Plz enter start to start.\n");
        }
    }
    return 0;
}

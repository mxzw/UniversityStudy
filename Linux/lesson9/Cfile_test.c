#include <stdio.h>

int main()
{
    //FILE *fopen(const char *path, const char *mode);
    FILE* fp = fopen("./bite","w+");
    
    //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    //size_t fwrite(const void *ptr, size_t size, size_t ,FILE *stream);
    char buf[] = "linux so easy!";
    fwrite(buf,1,sizeof(buf),fp);

    fseek(fp,0,SEEK_SET);

    char buf1[1024] = {0};
    fread(buf1,1,sizeof(buf),fp);
    printf("%s\n",buf1);

    fclose(fp);

    return 0;
}

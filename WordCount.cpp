#include <stdio.h>
#include <string.h>

int *getCharNum(char *filename, int *totalNum);

int main(){
    char filename[30];
    // totalNum[0]: 总行数  totalNum[1]: 总字符数  totalNum[2]: 总单词数
    int totalNum[3] = {0, 0, 0};
    
    char chars[2];
    printf("Input your choice: ");
    gets(chars);
    
    printf("Input file name: ");
    scanf("%s", filename);

    if(getCharNum(filename, totalNum)){
        if(chars[1]=='c')
        {
        	printf("总字符数:%d",totalNum[1]);
		}
		
		else if(chars[1]=='w')
		{
			printf("总单词数:%d",totalNum[2]);
		}
    }else{
        printf("Error!\n");
    }

    return 0;
}

/**
 * 统计文件的字符数、单词数、行数
 *
 * @param  filename  文件名
 * @param  totalNum  文件统计数据
 *
 * @return  成功返回统计数据，否则返回NULL
**/
int *getCharNum(char *filename, int *totalNum){
    FILE *fp;  
    char buffer[1003];  
    int bufferLen;  
    int i;  
    char c;  
    int isLastBlank = 0;  
    int charNum = 0;  
    int wordNum = 0; 

    if( (fp=fopen(filename, "rb")) == NULL ){
        perror(filename);
        return NULL;
    }

    
    while(fgets(buffer, 1003, fp) != NULL){
        bufferLen = strlen(buffer);
        // 遍历缓冲区的内容
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // 遇到空格
                !isLastBlank && wordNum++;  // 如果上个字符不是空格，那么单词数加1
                isLastBlank = 1;
            }else if(c!='\n'&&c!='\r'){  // 忽略换行符
                charNum++;  // 如果既不是换行符也不是空格，字符数加1
                isLastBlank = 0;
            }
        }

        !isLastBlank && wordNum++;  // 如果最后一个字符不是空格，那么单词数加1
        isLastBlank = 1;  // 每次换行重置为1

        // 一行结束，计算总字符数、总单词数、总行数
        totalNum[0]++;  // 总行数
        totalNum[1] += charNum;  // 总字符数
        totalNum[2] += wordNum;  // 总单词数

    

        // 置零，重新统计下一行
        charNum = 0;
        wordNum = 0;
    }

    return totalNum;
}

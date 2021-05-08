#include <stdio.h>
#include <string.h>

int *getCharNum(char *filename, int *totalNum);

int main(){
    char filename[30];
    // totalNum[0]: ������  totalNum[1]: ���ַ���  totalNum[2]: �ܵ�����
    int totalNum[3] = {0, 0, 0};
    
    char chars[2];
    printf("Input your choice: ");
    gets(chars);
    
    printf("Input file name: ");
    scanf("%s", filename);

    if(getCharNum(filename, totalNum)){
        if(chars[1]=='c')
        {
        	printf("���ַ���:%d",totalNum[1]);
		}
		
		else if(chars[1]=='w')
		{
			printf("�ܵ�����:%d",totalNum[2]);
		}
    }else{
        printf("Error!\n");
    }

    return 0;
}

/**
 * ͳ���ļ����ַ�����������������
 *
 * @param  filename  �ļ���
 * @param  totalNum  �ļ�ͳ������
 *
 * @return  �ɹ�����ͳ�����ݣ����򷵻�NULL
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
        // ����������������
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // �����ո�
                !isLastBlank && wordNum++;  // ����ϸ��ַ����ǿո���ô��������1
                isLastBlank = 1;
            }else if(c!='\n'&&c!='\r'){  // ���Ի��з�
                charNum++;  // ����Ȳ��ǻ��з�Ҳ���ǿո��ַ�����1
                isLastBlank = 0;
            }
        }

        !isLastBlank && wordNum++;  // ������һ���ַ����ǿո���ô��������1
        isLastBlank = 1;  // ÿ�λ�������Ϊ1

        // һ�н������������ַ������ܵ�������������
        totalNum[0]++;  // ������
        totalNum[1] += charNum;  // ���ַ���
        totalNum[2] += wordNum;  // �ܵ�����

    

        // ���㣬����ͳ����һ��
        charNum = 0;
        wordNum = 0;
    }

    return totalNum;
}

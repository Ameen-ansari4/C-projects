#include <stdio.h>

int main(int argc, char* argv[]){
	int c;
	int inside = 0;
	FILE *src, *des;

	if(argc < 2){
		printf("Requires file name!(src, des)\n");
		return -1;
	}

	//to remove spaces at the start of the lines
	if((src = fopen(argv[1], "r")) && (des = fopen("file1.txt", "w"))){
		while((c = fgetc(src)) != EOF){
			if(!inside && (c == ' ' || c == '\t')) continue;

			inside = 1;
			fputc(c, des);
			if(c == '\n') inside = 0;
		}

		fclose(src);
		fclose(des);
	}else{
		printf("Couldn't access the file!!\n");
		return -1;
	}

	//To remove spaces at the end of the line
	if((src = fopen("file1.txt", "r")) && (des = fopen("file2.txt", "w"))){
		inside = 0;
		fseek(src, -1, SEEK_END);
		for(int pos = ftell(src); pos >= 0; pos--){
			fseek(src, pos, SEEK_SET);
			c = fgetc(src);
			if(!inside && (c == ' ' || c == '\t')){
				continue;
			}
			inside = 1;
			fputc(c, des);
			if(c == '\n') inside = 0;
		}

		fclose(src);
		fclose(des);

		remove("file1.txt");
	}else{
		printf("Couldn't access the file!!\n");
		return -1;
	}

	//the file is written backward in file2.txt
	//save it into original file flipping the characters again
	
	if((src = fopen("file2.txt", "r")) && (des = fopen(argv[1], "w"))){
		fseek(src, -1, SEEK_END);
		for(int pos = ftell(src); pos >=0; pos--){
			fseek(src, pos, SEEK_SET);
			c = fgetc(src);
			fputc(c, des);
		}

		fclose(src);
		fclose(des);

		remove("file2.txt");
	}else{
		printf("Couldn't access the file!!\n");
		return -1;
	}
	return 0;
}

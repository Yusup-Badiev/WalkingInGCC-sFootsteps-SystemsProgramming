#include <stdio.h>
#include <stdlib.h>

char logOperater[3][4] =
{
  "NOT",
  "OR",
  "AND"
};

char arithOperater[4][2] =
{ 
  "-",
  "+",
  "*",
  "/"
};

char arithOperand[10][2] =
{ 
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "0"
};

char logOperand[2][6] =
{
  "true",
  "false"
};

int SizeOf(char* String){
        int size = 0;
        while(String[size] != '\0') size++;
        return size;
}

int CompareStrings(char* S1, char* S2){
	int i = 0;
	int size1 = SizeOf(S1);
	int size2 = SizeOf(S2);
	
	if(size1 > size2){
		for(i = 0; i <= size2; i++) if(S1[i] != S2[i]) return 0;	
	}
	else{
		for(i = 0; i <= size1; i++) if(S1[i] != S2[i]) return 0;
	}
	return 1;
}

void GetNextExpr(int* inputPtr, char* tokenBySem, char* argv[]){
	int i = 0;
	while(argv[1][*inputPtr] != ';' && argv[1][*inputPtr] != '\0'){
		tokenBySem[i] = argv[1][*inputPtr];
		i++;
		(*inputPtr)++;
	}
	tokenBySem[i] = '\0';
	(*inputPtr)++;
}

int ParseBySpace(char** ArrTokens, char* tokenBySem, int Exper, int NoSpace){
	int size = SizeOf(tokenBySem);
	int i = 0;
	int copy = 1;
	int indexOfToken = 0;
	
	for(i = 0; i < size; i++){
		if(!NoSpace){
			tokenBySem[0] = 0;
			NoSpace = 1;
			continue;
		}
		
		if(i == 0 || (*(tokenBySem + i - 1) == 0 && *(tokenBySem + i) == ' ')){
			copy = 0;
			ArrTokens[indexOfToken++] = tokenBySem + i;
		}
		
		else if(*(tokenBySem + i) == ' '){
			*(tokenBySem + i) = 0;
			copy = 1;
		}
		
		else{
			if(copy) {
				ArrTokens[indexOfToken++] = tokenBySem + i;
				copy = 0;
			}
		}
	}
	
	return indexOfToken;
}

int isArOperater(char* str){
	int i = 0;

        for(i = 0; i < 4; i++){
		//printf("%s ===== %s = %d\n", str, arithOperater[i], CompareStrings(str, arithOperater[i]));
                if(CompareStrings(str, arithOperater[i])) return 1;
        }

	return 0;
}

int isLogOperater(char* str){
	int i = 0;
	
	for(i = 0; i < 3; i++){
		//printf("%s ===== %s = %d\n", str, logOperater[i], CompareStrings(str, logOperater[i]));
                if(CompareStrings(str, logOperater[i])) return 1;
        }

	return 0;
}

int isLogOperand(char* str){
	int i = 0;
	
	for(i = 0; i < 2; i++){
		//printf("%s ===== %s = %d\n", str, logOperand[i], CompareStrings(str, logOperand[i]));
                if(CompareStrings(str, logOperand[i])) return 1;
        }

	return 0;
}

int isArOperand(char* str){
	int i = 0;
	
	for(i = 0; i < 10; i++){
		//printf("%s ===== %s = %d\n", str, arithOperand[i], CompareStrings(str, arithOperand[i]));
                if(CompareStrings(str, arithOperand[i])) return 1;
        }

	return 0;
}

int unidentifed(char* str){
	if(isArOperater(str)) {
		return 0;
	}
	
	if(isLogOperater(str)) {
		return 0;
	}
	
	if(isLogOperand(str)) {
		return 0;
	}
	
	if(isArOperand(str)){
		return 0;
	}
		
	return 1;
}

int removeBeginUnknown(char **arrTokens, int numOfTokens, int expr) {
	int i = 0;
	
	while(i < numOfTokens){
		if(!unidentifed(arrTokens[i])){
			break;
		}
		
		printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown identifier", arrTokens[i]);
		i++;
	}
	
	int j = i;
	int k = 0;
	
	for(j = i; j < numOfTokens; j++){
		arrTokens[k] = arrTokens[j];
		k++;
	}
	
	return numOfTokens - i;
}

int InExperFirst(char * str, int expr) {
	if(isLogOperand(str) || isArOperand(str)){
		return 0;
	}
	printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Unexpected operator", str);
	return 1;
}

int errorInExpr(char **arrTokens, int numOfTokens, int expr){
	InExperFirst(arrTokens[0], expr);
	int i = 0;
	int op = 0;
	int op2 = 0;
	int errors = 0;
	
	for(i = 0; i < numOfTokens && !op; i++){
		//printf("%s\n", arrTokens[i]);
		
		if(op2){
			op = 1;
			if(i == numOfTokens - 1){
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Missing operand", "");
                        }
			
			else if(unidentifed(arrTokens[i + 1])){
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown operand", arrTokens[i + 1]);
                        }
		}
		
		else if(isArOperater(arrTokens[i]) || isLogOperater(arrTokens[i])) {
			op = 1;
			
			if(i == numOfTokens - 1){
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Missing operand", "");
			}
			
			else if(unidentifed(arrTokens[i + 1])){
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown operand", arrTokens[i + 1]);
			}
			
			else if(isArOperater(arrTokens[i+1]) || isLogOperater(arrTokens[i+1])){
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Unexpected operator", arrTokens[i+1]);
			}
			
			else if(!(isArOperater(arrTokens[i]) &&  isArOperand(arrTokens[i + 1])) && !(isLogOperater(arrTokens[i]) && isLogOperand(arrTokens[i + 1]))) {
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Operand type mismatch", arrTokens[i + 1]);
			}
		}
		
		else if(unidentifed(arrTokens[i]) && unidentifed(arrTokens[i-1])) {
			errors++;
			printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown identifier", arrTokens[i]);
		}
		
		else if(isLogOperand(arrTokens[i]) || isArOperand(arrTokens[i]) && i != numOfTokens - 1) {
			if(isArOperand(arrTokens[i+1]) || isLogOperand(arrTokens[i+1])){
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Unexpected operand", arrTokens[i+1]);
                        }
			
			else if(unidentifed(arrTokens[i+1])){
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown operator", arrTokens[i+1]);
				op2 = 1;
			}
			
			else if(!(isArOperater(arrTokens[i+1]) &&  isArOperand(arrTokens[i])) && !(isLogOperater(arrTokens[i+1]) && isLogOperand(arrTokens[i]))) {
				errors++;
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Operator type mismatch", arrTokens[i + 1]);
                        }
		}
	}
	
	if(!op){
		errors++;
		printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Missing operator", "");
	}
	
	if(i+1 >= numOfTokens && !errors) return 0;
	
	errorNotEnded(arrTokens, numOfTokens, i+1, 1, expr);

	return 1;
}

void errorFirstNE(char* str, int expr){
	
	if(unidentifed(str)) {
		printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown identifier", str);
	}
	
	else if(isArOperand(str) || isLogOperand(str)) {
		printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Unexpected operand", str);
	}
	
	else {
		printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Unexpected operater", str);
	}
}

int errorNotEnded(char **arrTokens, int numOfTokens, int start, int fir, int expr){
	int re = 0;
	if(start < numOfTokens){
		if(fir) {
			printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Expression wasn't ended" , "");
		}
		re = 1;
	}
	else{
		return 0;
	}
	
	int i;
	int op2 = 0;
	int op = 0;
	
	errorFirstNE(arrTokens[start], expr);
	
	for(i = start; i < numOfTokens - 1 && !op; i++) {
		//printf("%s\n", arrTokens[i + 1]);
		
                if(op2){
                        op = 1;
			
                        if(unidentifed(arrTokens[i + 1])){
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown operand", arrTokens[i + 1]);
                        }
                }
		
                else if(isArOperater(arrTokens[i]) || isLogOperater(arrTokens[i])) {
                        op = 1;
			
                        if(unidentifed(arrTokens[i + 1])){
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown operand", arrTokens[i + 1]);
                        }
			
                        else if(isArOperater(arrTokens[i+1]) || isLogOperater(arrTokens[i+1])){
                                printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Unexpected operater", arrTokens[i+1]);
                        }
			
                        else if(!(isArOperater(arrTokens[i]) &&  isArOperand(arrTokens[i + 1])) && !(isLogOperater(arrTokens[i]) && isLogOperand(arrTokens[i + 1]))) {
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Missing operand", "");	
                        }
                }
		
                else if(unidentifed(arrTokens[i]) && unidentifed(arrTokens[i+1])) {
			printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown identifier", arrTokens[i+1]);
                }
		
                else if(isLogOperand(arrTokens[i]) || isArOperand(arrTokens[i])) {
                        if(isArOperand(arrTokens[i+1]) || isLogOperand(arrTokens[i+1])) {
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Unexpected operand", arrTokens[i+1]);
                        }
			
                        else if(unidentifed(arrTokens[i+1])) {
				printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Parse Error", expr, "Unknown operator", arrTokens[i+1]);
                                op2 = 1;
                        }
			
                        else if(!(isArOperater(arrTokens[i+1]) &&  isArOperand(arrTokens[i])) && !(isLogOperater(arrTokens[i+1]) && isLogOperand(arrTokens[i]))) {
                                printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "Operator type mismatch", arrTokens[i + 1]);
                        }
                }
	}
	
	if(i < numOfTokens) errorNotEnded(arrTokens, numOfTokens, i + 1, 0, expr);
	
	return re;
}

int main(int argc, char *argv[]) {
	printf("\n\n");
	
	int inputPtr = 0;
	char* tokenBySem = malloc((SizeOf(argv[1])+1)*sizeof(char));
	char* tokenBySem2 = malloc((SizeOf(argv[1])+1)*sizeof(char));
	
	int expr = 0;
	while(inputPtr <= SizeOf(argv[1])){
		GetNextExpr(&inputPtr, tokenBySem, argv); // puts Stirng of next expression into tokenBySem
		
		tokenBySem2 = tokenBySem;
		expr++;
		
		if(!SizeOf(tokenBySem)) {
			
			printf("Improperly formated");
			printf("<error type> in expression %d: <description> in:\n\t<expression error was found in, or expression fragment/token> \n\n", "", expr, "", "");
			continue;
		}
		
		int noSpace = !(tokenBySem[0] == ' ');
		
		char **arrTokens = malloc((SizeOf(tokenBySem)+1)*sizeof(char *));       // Makes a 2d array of chars to hold tokens
		int i = 0;								//
		for(i = 0; i < SizeOf(tokenBySem)+1; i++){				//
			arrTokens[i] = malloc((SizeOf(tokenBySem)+1)*sizeof(char));	//
		}
		
		int numOfTokens = ParseBySpace(arrTokens, tokenBySem, expr, noSpace);  // parces sting by spaces and puts the tokens into arrTokens, then return int number of tokens
		
		int numOfTokens2 = removeBeginUnknown(arrTokens, numOfTokens, expr);
		
		int error = (numOfTokens != numOfTokens2);
		
		numOfTokens = numOfTokens2;
		
		if(!numOfTokens || noSpace) {
			printf("%s in expression %d: %s in:\n\t\"%s\" \n\n", "Scan Error", expr, "incomplete expression", "");
			//printf("\n--------------------------------------------------\n");
                        continue;
                }
		
		int ok = !(errorInExpr(arrTokens, numOfTokens, expr));

		if(ok && !error){
			printf("Expression %d:\n\tOK.\n\n", expr);
		}
		
		//printf("\n--------------------------------------------------\n");
	}
	return 0;
}

#include<stdio.h>
#include<math.h>
int n(char s){//判断字符的类型 
	if(48<=s&&s<=57){
		return s-48;
	}else if(s=='.'){
		return -1;
	}else if(s=='+'||s=='-'||s=='*'||s=='/'){
		return -2;
	}else if(s=='('){
		return -3;
	}else if(s==')'){
		return -4;
	}else if(s=='^'){
		return -5;
	}else if(s=='s'){
		return -7;
	}else if(s=='c'){
		return -8;
	}else if(s=='t'){
		return -9;
	}else if(s=='a'){
		return -10;
	}else if(s=='l'){
		return -11;
	}else if(s=='f'){
		return -12;
	}else if(s=='e'||s=='p'||s=='x'){
		return -50;
	}else if(s=='\0'){
		return -99;
	}else{
		return -100;
	}
}




void getnum(char arr[],int*i,int*top,double stk[],double x){
	*top+=1;
	stk[*top]=0;
	if(arr[*i]=='x'){
		(*i)++;//括号不能省略 
		stk[*top]=x;
		goto flag;
	}else if(arr[*i]=='e'){
		(*i)++;
		stk[*top]=M_E;
		goto flag;
	}else if(arr[*i]=='p'){
		(*i)=(*i)+2;
		stk[*top]=M_PI;
		goto flag;
	}
	while(n(arr[*i])>=0){
		stk[*top]=stk[*top]*10+n(arr[*i]);
		*i+=1;
	}
	if(n(arr[*i])==-1){//考虑有小数的情况 
		*i+=1;
		double ex=1;
		double deci=0;
		while(n(arr[*i])>=0){
			deci=deci*10+n(arr[*i]);
			ex*=10;
	        *i+=1;
		}
		stk[*top]+=deci/ex;
	}
	flag:
	if(arr[*i]=='!'){
		if(stk[*top]!=(int)stk[*top]||stk[*top]<0){
			printf("Error! For [expression]!, the expression has to be a natural number\n");
			system("pause");
		}else{
			if(stk[*top]==0){
				stk[*top]=1;
			}else{
				int j;
				for(j=stk[*top]-1;j>0;j--){
			    stk[*top]*=j;
		        }
			}
		    (*i)++;
		}
	}
}




double cal(char arr[],double x){
	double stk[100]={0};
	char sign[100];
	int top=-1;
	int i=0;
	int j;
	int mul=0;
	int div=0;
	getnum(arr,&i,&top,stk,x);
	if(i!=0){
		mul=1;
	}
	while(arr[i]!='\0'){
		if(n(arr[i])==-2){//读取到运算符 
		    if(arr[i]=='/'){
		    	div=1;
			}
			if(arr[i]=='+'||arr[i]=='-'){
				div=0;
			}
			top+=1;
			sign[top]=arr[i];
			i++;
			mul=0;
		}
		if(n(arr[i])==-3){//读取到‘(’ 
		    if(mul==1){
		    	top++;
		    	sign[top]='*';
			}
			top+=1;
			sign[top]=arr[i];
			i++;
			mul=0;
		}
		if(n(arr[i])==-4){//读取到‘)’ 
			i++;
			double ans=0;
			while(sign[top-1]!='('){//得出括号内的结果 
				if(sign[top-1]=='-'){
					ans-=stk[top];
				}else if(sign[top-1]=='+'){
					ans+=stk[top];
				}
				top-=2;
			}
			top--;
			sign[top]='\0';
			stk[top]=ans+stk[top+1];
			mul=1;
			goto flag;
		}
		if(n(arr[i])==-5){//读取到幂运算符 
			i++;
			if(arr[i]!='('){
				getnum(arr,&i,&top,stk,x);
			    top--;
			    stk[top]=pow(stk[top],stk[top+1]);	
				goto flag;
		    }
			else{
				int cnt=1;
				int cur=0;
				char s[100];
				i++;
				while(cnt>0){
					s[cur]=arr[i];
					cur++;
					if(arr[i]=='('){
						cnt++;
					}else if(arr[i]==')'){
						cnt--;
					}
					i++;
				}
				s[cur-1]='\0';
				stk[top]=pow(stk[top],cal(s,x));
				goto flag;
			}
		}
		if(n(arr[i])<=-7&&n(arr[i])>=-20){//读取到特殊运算符
		    if(mul==1){
		    	top++;
		    	if(div==0){
		    		sign[top]='*';
				}else{
					sign[top]='/';
				}
			}
		    j=n(arr[i]);
		    while(arr[i]!='('){
		    	i++;
			}
		    int cnt=1;
			int cur=0;
			char s[100];
			double start,end;
			i++;
			if(j==-12){
				while(arr[i]!=','){
					s[cur]=arr[i];
					cur++;
					i++;
				}
				s[cur]='\0';
				start=cal(s,0);
				i++;
				cur=0;
				while(arr[i]!=','){
					s[cur]=arr[i];
					cur++;
					i++;
				}
				s[cur]='\0';
				end=cal(s,0);
				i++;
				cur=0;
			}
			while(cnt>0){
				s[cur]=arr[i];
				cur++;
				if(arr[i]=='('){
					cnt++;
				}else if(arr[i]==')'){
					cnt--;
				}
				i++;
			}
			s[cur-1]='\0';
			top++;
			switch(j) {
		    	case -7:
		    	    stk[top]=sin(cal(s,x));
		    	    break;
		    	case -8:
		    		stk[top]=cos(cal(s,x));
		    	    break;
		    	case -9:
		    		stk[top]=tan(cal(s,x));
		    	    break;
		    	case -10:
		    		stk[top]=pow(pow(cal(s,x),2),0.5);
		    	    break;
		    	case -11:
		    		if(cal(s,x)<=0){
		    			printf("Error! For ln([expression]), the expression has to be greater than 0\n");
			            system("pause");
					}else{
						stk[top]=log(cal(s,x));
		    	        break;
					}
				case -12:
					stk[top]=0;
					double temp=0;
					double k;
					double step;
					if(end<=start){
						printf("Error! For f(a,b,expr), a has to be less than b\n");
						system("pause");
					}
					else if(end-start>1){
						step=(end-start)/10000000.0;
					}
					else{
						step=0.0000001;
					}
					for(k=start;k<end;k+=step){
						temp+=cal(s,k);
						cnt+=1;
						if(cnt==100000){
							stk[top]+=(temp/10000000);
							cnt=0;
							temp=0;
						}
					}
					if(temp>0){
						stk[top]+=temp/100000000;
					}
					stk[top]*=(end-start);
			}
			goto flag;
		}
		if(n(arr[i])==-100){
			printf("invalid symbol!\n");
			system("pause");
		}
		if(n(arr[i])==-50||n(arr[i])>=0){
			if(mul==1){
				top++;
				if(div==0){
					sign[top]='*';
				}else{
					sign[top]='/';
				}
			}
		}
		getnum(arr,&i,&top,stk,x);
		mul=1;
		flag:
		while(top>1){
			if(sign[top-1]=='('||arr[i]=='^'||arr[i]=='!'){
			    break;
		   }else if(sign[top-1]=='*'){//处理乘除法 
			    stk[top-2]*=stk[top];
			    top-=2;
		   }else if(sign[top-1]=='/'){
				if(stk[top]==0){
					printf("0\n");
					printf("The divisor can't be zero!\n");
					system("pause");
				}
				stk[top-2]/=stk[top];
				top-=2;
		    }else{
		    	break;
			}
		}
	}
	double ans=stk[0];
	while(top>0){//处理剩余加减法 
		if(sign[top-1]=='-'){
			ans-=stk[top];
		}else if(sign[top-1]=='+'){
			ans+=stk[top];
		}else{
			ans+=stk[top];//针对括号开头的情况 
		}
		top-=2;
	}
    return ans;
}
double solver(char l[],char r[],double x,int cnt){
	double ansl=cal(l,x);
	double ansr=cal(r,x);
	double j=0.000000000001;
	if(ansl-ansr>j||ansr-ansl>j){
		double deri=(cal(l,x+j)-cal(r,x+j)-cal(l,x-j)+cal(r,x-j))/2/j;
		if(deri==0||cnt>100){
			printf("Please try again (still in three lines)\n");
			scanf("%s\n%s\n%lf",l,r,&x);
			return solver(l,r,x,0);
		}else{
			x-=(ansl-ansr)/deri;
		}
		cnt++;
		return solver(l,r,x,cnt);
	}
	return x;
}
int main()
{
	char l[100];
	char r[100];
	char s[200];
	double x;
	char choice[100];
	printf("Welcome to use this calculator!\n\n");
	printf("Supported inputs:\n");
	printf("Operations: +,-,*,/,^,!   Functions:sin(),cos(),tan(),abs(),ln(),f(a,b,expr)   Symbols:e,pi,() \n\n");
	printf("Note: '()' of all functions can't be omitted   eg.ln2 must be written as ln(2)\n");
	printf("      f(a,b,expr) means integral from a to b, for f(x)=expr\n ");
	printf("      and make sure your keyboard is in English mode\n\n");
	printf("Enter 1 for basic calculation, and 2 for linear function solving");
	printf(" (you can also change the mode later by entering 'R')\n");
	scanf("%s",choice);
	while(choice[0]!='1'&&choice[0]!='2'||choice[1]!='\0'){
		printf("Please re-enter your mode choice:\n");
		scanf("%s",&choice);
	}
	while(choice>0){
		if(choice[0]=='1'){
			printf("Please enter your expression: \n");
			while(scanf("%s",s)==1){
				if(s[0]=='R'){
					choice[0]='2';
					break;
				}
				double ans=cal(s,0);
		        printf("%.10g\n",ans);
		        printf("Please enter your expression: \n");
		    }
	    }
		if(choice[0]=='2'){
			printf("Please enter the expression on left side of the equation,");
			printf(" the expression on right side,");
			printf(" and the approximate value of x  in the following three lines: \n");
			while(1==scanf("%s",l)){
				if(l[0]=='R'){
					choice[0]='1';
					break;
				}
				scanf("\n%s\n%lf",r,&x);
			    printf("x=%.10g\n",solver(l,r,x,0));
				printf("Please enter the expression on left side of the equation,");
				printf(" the expression on right side,");
				printf(" and the approximate value of x in the following three lines: \n");
			}
		}
	}
	system("pause");
	return 0;
}

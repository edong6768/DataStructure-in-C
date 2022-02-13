2. Reverse.c
 ※main함수
   -변수선언
     ①Stack* a : 스택
     ②Element(=int) e : 입력되는 수들
    -실행
     1) 입력값: e=>Push(Stack* a, int e) : 반복 until ctrl-D
     2) 입력종료 후 => while(IsEmptyStack) : print(Pop(Stack* a))
     3) DestroyStack(a)

3. Convert.c
 ※main함수
   -변수선언
     ①Stack* a :스택
     ②Element(=int) num : 입력된 10진수 표현의 수
     ③Element div (초기값=num):  2로 나누어질 대상, 10진표현을 2로 나눈 몫
     ④Element remainder : div(초기값=num)을 2로 나눈 나머지
   -실행
     1) 값 입력 scan(num)
     2) div=num
     3) 반복문: while(div!=0){remainder=div%2=>Push(Stack* a, int remainder); div/=2}
         -> div를 2로 나눈 나머지를  Stack* a로 push
     4) 반복문: while(IsEmptyStack){print(Pop(Stack *a))} -> Stack a에 든 나머지값들을 Pop
     5) DestroyStack(a)

4. Calculator.c
 ※함수
    ①int TestExpr(char* str): 입력된 수식이 (return -1)infix표현이 아니며, 이항연산표현이 틀렸는지, 
                                               (return 1)괄호쌍이 틀린지 확인 후 모두 통과하면 (return 0)
    ②char* Postfix(char* str): 입력된 수식을 Postfix표현으로 변환한 문자열로 반환, 수와 연산자 사이에는 한칸씩 띄어져있다.
    ③int CalPost(char* strp): Postfix형태로 표현된 수식의 결과값을 계산하여 반환

 ※main함수
   -변수선언
     ①char str[50] : infix표현 수식(입력)
     ②char* strpost : postfix 표현 수식
   -실행
     1) 수식 문자열 입력 scan(str)
     2) switch(TestExpr(char* str)) : 입력 수식에서 오류 확인 후 적당한 오류메시지 출력 및 종료
     3) print: strpost=Postfix(char* str) : str를 Postfix로 변환한 문자열의 포인터을 strpost에 할당 후 출력
     4) print: CalPost(char* strpost) : strpost의 Postfix수식을 계산한 값을 출력

 ※TestExpr함수
   -변수선언
     ①int kets=0 : 쌍이 없는 괄호의 수('('=>++, ')'=>-- / 이 값은 0이어야 테스트를 통과한다)
     ②int num_op=0 : 수식에서 수와 연산자의 개수 합산(수=>++, 연산자=>--, 문자열을 읽으면서 이 값은 0 또는 1이어야 한다)
   -실행
     1) 반복문 시작: for(int i=0; str 길이동안 i++)
     2) if(isdigit(str[i]) == false)  :  str[i]가 수가 아니면
            switch(str[i]) case 연산자: num_op--
                                   case '(' : ket++
                                   case ')' : ket--
         else if(isdigit(str[i+1]==false) : str[i]가 수이며, str[i+1]은 수가 아닐때 => 수와 연산자 경계의 개수
               num_op++                                                                                                   (두자리 이상 수를 하나로 세기 위해어)
      
     3) if(num_op: 0 또는 1이 아니면) : return -1 => 수 사이 연산자가 있으므로,  문자열을 읽어가면 항상 수가 1개 더 많거나
                                                                                      수와 연산자의 개수가 같다(ex [9 + ] or  [9 + 10] )
     4) 반복문 종료
     5) if(ket != 0) return 1 => 쌍을 이루지 않은 괄호가 존재할 때
     6) return 0; => 모두 통과하면 정상이라고 반환

 ※Postfix함수
   -변수선언
     ①Stack* op: 연산자를 넣을 스택
     ②char* strpost: Postfix 표현의 수식이 들어갈 문자열
     ③int count=0; strpost내의 현재 입력위치(ex strpost[count])
   -실행
     1) 반복문 시작: for(int i=0; str 길이동안 i++)
      |  2) if(isdigit(str[i]) == false)  :  str[i]가 수가 아니면
      |       (a)  if (isdigit(strpost[count - 1]) != 0) strpost[count++] = ' ' : strpost에서 직전에 수가 입력되었다면 빈칸을 넣기
      |     3) switch(str[i]) 
      |       (1) case '+' or '-' : 3순위 연산자
      |             (b)반복문: while(IsEmptyStack(op)==false && str[Top(op)]!='(') : stack이 비거나 top이 열린괄호(일때 까지
      |               |      (c) strpost[count++]=str[Pop(op)]; strpost[count++]=' ' : stack의 연산자를 빼내서 strpost입력하고 빈칸으로 띄운다
      |             ===>앞서 있었던 연산자에 상관없이 모두 strpost에 입력(stack{+ *}일 때 strpost에 " * + "를 입력) 
      |             Push(op,i) : 현재 str[i]의 값(정수stack이므로 char값 대신 문자열 위치값으로)을 stack에 Push 
      |       (2) case '*' or '%' : 2순위 연산자
      |             if (str[Top(op)] == '*' || str[Top(op)] == '%') : 만약 top에 * 나 %가 있으면(동순위의 연산자가 있으면)
      |              |      (c) strpost[count++]=str[Pop(op)]; strpost[count++]=' ' : stack의 연산자를 빼내서 strpost입력하고 빈칸으로 띄운다
      |              ===>앞서 있었던 동순위의 연산자(*,%)에 대해서만 strpost에 입력
      |       (3) case '(' : Push(op, i) : 열는괄호를 stack에 넣는다
      |       (4) case ')'
      |             (b')반복문: while( str[Top(op)]!='(') : stack의 top이 열린괄호(일때 까지
      |               |      (c) strpost[count++]=str[Pop(op)]; strpost[count++]=' ' : stack의 연산자를 빼내서 strpost입력하고 빈칸으로 띄운다
      |              ===>괄호 뒤에 있던 모든 연산자를 strpost에 입력
      |             Pop(op) : 열는괄호는 stack에서 빼낸다
     ========================================================================
        요약: ① 연산자를 처리하기 전에 숫자가 입력되었다면 한칸 띄운다(두자리 이상 수를 위해 숫자끼리는 띄우지 않는다)
                 ② 열는괄호가 stack에 있다면 닫는괄호가 나타나기 전까지는 열린괄호 뒤의 연산자에 대해서만 처리한다.
                 ③ 2순위 연산자:직전의 연산자가 ┌ 3순위: Pop하지 않고 그대로 두고 Push
                                                                        └ 2순위(동순위): 직전을 Pop한 뒤 Push
                 ④ 3순위 연산자:직전 연산자에 상관없이 모두 Pop하여 strpost에 입력한다.
     ========================================================================

     3) else : strpost[count++]=str[i] : 숫자는 바로 strpost에 넣는다
     4) (a) if (isdigit(strpost[count - 1]) != 0) strpost[count++] = ' ' : strpost에서 직전에 수가 입력되었다면 빈칸을 넣기
     5) (b'')반복문: while(IsEmptyStack(op)==false) : stack이 빌 때까지
                  (c) strpost[count++]=str[Pop(op)]; strpost[count++]=' ' : stack의 연산자를 빼내서 strpost입력하고 빈칸으로 띄운다
           ===>앞서 있었던 연산자에 상관없이 모두 strpost에 입력
     6) DestroyStack(op); return strpost

 ※CalPost함수
   -변수선언
     ①Stack* cal: 연산이 이루어질 스택
     ②char* tok=strtok(strp, " "): Postfix 표현의 수식을 빈칸기준으로 token화
     ③int n1,n2: 연산하기 위한 정수 변수
   -실행
     1) 반복문 while(tok != NULL): token이 없을 때 까지
     2)if (isdigit(*tok) != 0) Push(cal, atoi(tok)) : token이 수이면, 정수화 한 뒤 stack에 Push한다
     3)else : token이 연산자이면
     4) n2, n1=Pop(cal) : 스택 내 2개의 정수를 계산을 위해 Pop
          op=tok[0]: switch문을 위해 char화
          switch(op){} : 각 연산자마다 연산실행한 후 그 값을 stack에 Push
     5) tok = strtok(NULL, " ") : 다음 token 가져오기
     6) n1 = Pop(cal) : DestroyStack 전 계산값만 가져오기
         DestroyStack(cal); return n1;
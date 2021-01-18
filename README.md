# 02_exam_rank42

<br/>

## Union

<br/>

- 1번째 2번째 순서대로 문자를 check 합니다.
- 한번 나온 문자는 다시 출력하지 않습니다.

<br/>

## Inter

<br/>

- 2번째 문자열에서 각 문자를 저장해 놓습니다.
- 1번째 문자열에서 각 문자를 확인하는데 2번째 문자열에 있었던 것을 출력합니다.
- 그리고 해당 문자는 더이상 출력하지 않습니다.

<br/>

## get_next_line

<br/>

- 반복하면서 하나씩 읽어오기 때문에 read()의 fd는 0이 되어야 합니다.
- '\n'까지 계속 arr에 추가를 하고 '\n'이 있는 경우에 line에 '\n' 전까지 저장하고
- arr는 free 해주고 다시 arr에 '\n'다음 부터 저장합니다.

<br/>

## printf

<br/>

- %가 나오면 flag(width, .precision만) 조사
- s,d,x에 맞춰서 출력을 해줍니다.

<br/>

### <조건>

<br/>

#### %s

<br/>

- va_arg(ap, char *);
- s == NULL 이면 s = "(null)"
- dot && precision < len => len = precision;
- 빈칸은 width - len
- 문자는 len

<br/>

#### %d

<br/>

- va_arg(ap, int);
- n == 0 && dot => len = 0;
- dot && precision > len => zero = precision - len;
- 빈칸은 width - (zero + len);
- '0'은 zero;
- 음수면 '-' 
- n == 0 && dot => return ;
- 숫자는 len;

<br/>

#### %x

<br/>

- va_arg(ap, unsigned int);
- n == 0 && dot => len = 0;
- dot && precision > len => len = precision - len;
- 빈칸은 width - (zero + len);
- '0'은 zero;
- n == 0 && dot => return ;
- 숫자느 len;

<br/>

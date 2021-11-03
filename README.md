## note
- [x] means `Yes` / `True` option
- [ ] means `No` / `False` option

## q1

### (a)
- [x] i 
- [x] ii
- [ ] iii
- [ ] iv
- [x] v
- [x] vi

### (b)
No.

Because only one instance here.

> When saying one functional dependencies that **hold** on schema $r(R)$, it means that 
> in every legal instance of $r(R)$ it satisfies the functional dependency.





## q2

### (a)

iv

### (b)



- [x] i (<img src="https://render.githubusercontent.com/render/math?math=$Q \rightarrow U \rightarrow V$" alt="">)

- [ ] ii 
- [x] iii  ($Q \rightarrow U \Rightarrow QS \rightarrow SU \rightarrow T$)
- [x] iv  ($QS \rightarrow SU \rightarrow R \rightarrow  W$)
- [x] v  ($(PQ \rightarrow S) \wedge (Q \rightarrow  U)  \Rightarrow PQ \rightarrow SU \rightarrow R \rightarrow W$)
- [ ] vi



Here, "$\wedge$" means logical conjunction "and".

### (c)

- [x] .

### (d)
- [ ] . 





## q3

### (a)

First, $AB \rightarrow A$,  $AB \rightarrow B$

$(AB \rightarrow B) \wedge (B \rightarrow CD) \Rightarrow AB \rightarrow BCD$

Therefore, $AB \rightarrow ABCD$

### (b)

Let $F=\{A \rightarrow B,\;  B \rightarrow CD,\;  E \rightarrow F\}$

- [x] i


$AB \cap BCD = B$ and $B \rightarrow BCD \; \in F^{+}$  $\Rightarrow AB \; and \; BCD$ is lossless

Furthermore,  $AB \cap EF, \; BCD \cap EF = \varnothing$

- [x] ii

$F_1=\{A \rightarrow B \}$, $F_2=\{A \rightarrow B \}$, $F_3=\{A \rightarrow B \}$

And thus, $F'=F_1 \cup F_2 \cup F_3 = F$,which means, of course, $F'^+ = F^+$.

### (c)

- [ ] i
- [x] ii

### (d)

- [x] i
- [ ] ii





## q4

### (a)

$candidate \; keys=\{RS\}, \{PQ \}$

### (b)

- [ ] 

### (c)

- [ ] i
- [x] ii
- [x] iii
- [ ] iv 
- [ ] v

### (d)

- [x] 

### (e)

- [x] i
- [x] ii
- [x] iii
- [x] iv
- [x] v

### (f)



### (g)

$R \rightarrow P$ violates BCNF,  thus we break  $\mathcal{E}$ in two parts:

+ $\mathcal{E}_1(RP)$, corresponding functional dependencies: $F_1 = \{R \rightarrow P\}$. now,  $\mathcal{E}_1$  is  in BCNF.
+ $\mathcal{E}_2(RQS)$, $F_2=\{S \rightarrow Q\}$, $F_2$ violates BCNF




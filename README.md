## note
- [x] means `Yes` / `True` option
- [ ] means `No` / `False` option

Since GitHub's markdown file don't support latex symbol, there is a pdf version in file `README.pdf`.

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



- [x] i ($Q \rightarrow U \rightarrow V$)

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

$\mathcal{E}$ itself is 3NF.

### (g)

$R \rightarrow P$ violates BCNF,  thus we break  $\mathcal{E}$ in two parts:



+ $\mathcal{E}_1(RP)$, corresponding functional dependencies: $F_1 = \{R \rightarrow P\}$. Now,  $\mathcal{E}_1$  is in BCNF.

+ $\mathcal{E}_2(RQS)$, $F_2=\{S \rightarrow Q\}$, $F_2$ violates BCNF

  

Break $\mathcal{E}_2$ into $\mathcal{E}_3(SQ)$ and $\mathcal{E}_4(SR)$ 

$\mathcal{E}_3$ is in BCNF but $\mathcal{E}_4$ does not, so we continue  break  $\mathcal{E}_4$ into: $\mathcal{E}_5(S),\; \mathcal{E}_6(R)$

Finally got one decomposition: $\mathcal{E}_1(RP), \; \mathcal{E}_3(SQ), \; \mathcal{E}_5(S),\; \mathcal{E}_6(R)$

To show this decomposition has as few tables as possible, one could see that the rest FDs which violates BCNF is $S \rightarrow Q$.

And the decomposition from $S \rightarrow Q$ leads to similar results except the difference in letters(R/S, P/Q). Thus both decomposition have the same number of tables .


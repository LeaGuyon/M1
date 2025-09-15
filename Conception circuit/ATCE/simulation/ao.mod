* +in (=1) -in (=2) out (=3) -- 100k=gain, rbw.cbw=LPF, eout=suiveur
.subckt opamp 1 2 3
rin 1 2 2meg
e 4 0 1 2 100k
rbw 4 3 0.5meg
cbw 3 0 31.85nf
.ends opamp

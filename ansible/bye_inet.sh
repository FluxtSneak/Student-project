
ssh H1 ip r d default 
ssh H1 ip r a default via 1.0.0.1
ssh H2 ip r d default 
ssh H2 ip r a default via 3.0.0.2

ssh H1 ip r d default 
ssh H2 ip r d default 
ssh H1 dhclient -v mgmt0
ssh H2 dhclient -v mgmt0


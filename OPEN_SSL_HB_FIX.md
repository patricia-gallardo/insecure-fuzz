# Review the actual fix for Heartbleed

Install Meld

~~~~bash
sudo apt install meld
~~~~

Get the before and after code

~~~~bash
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fixes/heartbleed/fixed.c
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fixes/heartbleed/vuln.c
~~~~

Diff them

~~~~bash
meld fixed.c vuln.c
~~~~

How does it compare to your solution?

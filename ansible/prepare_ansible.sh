#!/bin/bash

# Check that the input file was provided as an argument
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 input_file" >&2
  exit 1
fi

# Extract the hostnames from the input file using grep and awk
hostnames=$(grep -E '^Host ' "$1" | awk '{print $2}')

# Loop through each hostname and execute the command
for hostname in $hostnames; do
  echo "Running command for host $hostname"
  # Replace "echo" with your command
  ssh "$hostname" "hostname $hostname"
  ssh "$hostname" "useradd -m flo"
  ssh "$hostname" "echo flo:1234 | chpasswd"
  ssh "$hostname" "chmod ugo+w /etc/sudoers"
  ssh "$hostname" "echo 'flo ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers"
  ssh "$hostname" "chmod ugo-w /etc/sudoers"
  ssh-copy-id -i ~/.ssh/ansible.pub flo@"$hostname"
done

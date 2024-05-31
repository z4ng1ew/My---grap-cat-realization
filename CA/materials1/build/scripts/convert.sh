!/bin/bash
for file in *; do
  if [ -f "$file" ]; then
    sed -i 's/\r$//' "$file"
  fi
done
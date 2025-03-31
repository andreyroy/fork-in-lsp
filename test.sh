#!/usr/bin/env bash

test_dir="tests"
mkdir -p "$test_dir"

cat > "$test_dir/test.c" <<EOL
#include <stdio.h>
int main() {
    printf("Hello, World!\n");
    return 0;
}
EOL

cat > "$test_dir/test.cpp" <<EOL
int main() {
    int a;
    int b = a + 4;
}
EOL

declare -A expected_output
expected_output["test.c"]='{
  "tokens": [
    "#include <stdio.h>",
    "int",
    "main",
    "() {",
    "printf",
    "(\"Hello, World!\\n\");",
    "return 0;",
    "}"
  ]
}'
expected_output["test.cpp"]='{
  "tokens": [
    "int",
    "main",
    "() {",
    "int",
    "a",
    ";",
    "int",
    "b",
    "=",
    "a",
    "+ 4;",
    "}"
  ]
}'

# Запускаем тесты
for file in "$test_dir"/*; do
    filename=$(basename -- "$file")
    ./tokenize "$file" "tests/lsp_output.json" "tests/output.json"
    output=$(cat tests/output.json)
    
    if [ "$output" == "${expected_output[$filename]}" ]; then
        echo "✅ $filename: Тест пройден"
    else
        echo "❌ $filename: Ошибка! Ожидалось: ${expected_output[$filename]}, Получено: $output"
    fi
done

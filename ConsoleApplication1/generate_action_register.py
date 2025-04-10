import os
import re

def find_action_classes(directory, base_class="ActionNode"):
    action_classes = []
    pattern = re.compile(
        r'class\s+(\w+)\s*:\s*public(?:\s+virtual)?\s+[\w:]*' + re.escape(base_class)
    )

    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".h"):
                path = os.path.join(root, file)
                try:
                    try:
                        with open(path, "r", encoding="utf-8") as f:
                            content = f.read()
                    except UnicodeDecodeError:
                        with open(path, "r", encoding="cp949") as f:
                            content = f.read()

                    content = content.replace("\n", " ").replace("\r", " ")
                    matches = pattern.findall(content)
                    if matches:
                        print(f"[+] {path} 에서 찾음: {matches}")
                        action_classes.extend(matches)
                except Exception as e:
                    print(f"[!] {path} 열기 실패: {e}")
    return action_classes


def generate_register_code(class_names):
    lines = []
    includes = set()

    for cls in class_names:
        includes.add(f'#include "{cls}.h"')
        lines.append(f"REGISTER_ACTION({cls});")

    return "\n".join(sorted(includes)) + "\n\n#include \"ActionFactory.h\"\n\n" + "\n".join(lines)

def main():
    input_dir = "./"  # 현재 폴더 기준 (필요시 경로 수정)
    output_file = "autoregister.h"

    print(f" '{input_dir}' 안의 모든 .cpp/.h 파일을 탐색합니다...")
    classes = find_action_classes(input_dir)

    if not classes:
        print("등록할 클래스가 없습니다.")
        return

    print(f" 총 {len(classes)}개 클래스 발견!")

    code = generate_register_code(classes)

    with open(output_file, "w", encoding="utf-8") as f:
        f.write(code)

    print(f" '{output_file}' 파일 생성 완료! 프로젝트에 포함시키세요.")

if __name__ == "__main__":
    main()

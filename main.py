import os
import shutil

# path为批量文件的文件夹根目录
input_root = '.\\codefiles'
output_root = '.\\latexbuild\\codes'
tex_output_root = '.\\codes'
export = []

level = [r'\section', r'\subsection', r'\subsubsection']


def make_section(old_name, step):
    lv = level[min(max(step, 0), 2)]
    old_name = '-'.join(old_name.split('_'))
    old_name = '-'.join(old_name.split(' '))
    tex_sec = lv + '{' + old_name + '}'
    export.append(tex_sec)


def make_input(old_name, true_path):
    suf = old_name.split('.')[-1]
    if suf.count('c') > 0:
        suf = 'c++'
    elif suf.count('py') > 0:
        suf = 'python'
    elif suf.count('j') > 0:
        suf = 'java'
    elif suf.count('txt') > 0:
        suf = 'text'
    elif suf.count('md') > 0:
        suf = 'text'
    else:
        print("!!!ignore:" + old_name)
        return

    true_path = true_path.replace('\\', '/')
    tex_inp = '\\inputminted{' + suf + '}{' + true_path + '}'
    export.append(tex_inp)


file_reindex = 0


def rename_dfs(p, step):
    global file_reindex
    cur_path = os.path.join(input_root, p)
    file_names = os.listdir(cur_path)
    # print(file_names)

    for old_name in file_names:
        # print(old_name)
        new_name = str(file_reindex).zfill(3)
        old_path = os.path.join(input_root, p, old_name)
        new_path = os.path.join(output_root, new_name)

        if os.path.isdir(old_path):
            make_section(old_name, step)
            rename_dfs(os.path.join(p, old_name), step + 1)
        else:
            make_section(old_name, step)
            make_input(old_name, os.path.join(tex_output_root, new_name))
            shutil.copyfile(old_path, new_path)
            file_reindex = file_reindex + 1


if __name__ == '__main__':

    # 清空旧版本
    if os.path.exists(output_root):
        shutil.rmtree(output_root)

    os.mkdir(output_root)

    rename_dfs('', 0)

    with open('template.tex', 'r') as f:
        template = f.read()

    template = template.format('\n'.join(export))

    with open('.\\latexbuild\\main.tex', 'w+') as f:
        f.write(template)

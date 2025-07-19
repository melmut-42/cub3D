import os
import re

def replace_block_comments_with_blank_lines(code):
    pattern = re.compile(r'/\*[\s\S]*?\*/', re.MULTILINE)

    def replacer(match):
        comment = match.group(0)
        # count newlines in block comment
        lines = comment.count('\n')
        # replace whole block comment with same number of newlines + one newline less (to preserve lines)
        # if comment is single line with no \n, replace with empty string
        if lines == 0:
            return ''
        return '\n' * lines

    return pattern.sub(replacer, code)

def remove_single_line_comments_preserve_lines(code):
    lines = code.splitlines()
    new_lines = []
    for line in lines:
        # remove inline // comment
        line_no_comment = re.sub(r'//.*', '', line)
        # If line contained ONLY a comment, replace line with blank line
        if line.strip().startswith("//") and line_no_comment.strip() == '':
            new_lines.append('')
        else:
            new_lines.append(line_no_comment.rstrip())
    return '\n'.join(new_lines) + '\n'  # keep file ending newline

def clean_file(path):
    with open(path, 'r') as f:
        content = f.read()

    content = replace_block_comments_with_blank_lines(content)
    content = remove_single_line_comments_preserve_lines(content)

    with open(path, 'w') as f:
        f.write(content)

for root, _, files in os.walk('.'):
    for file in files:
        if file.endswith('.c') or file.endswith('.h'):
            clean_file(os.path.join(root, file))

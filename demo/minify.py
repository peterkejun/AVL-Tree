"""
Useful for compressing the program for use in contest programming where there is a file size limit.
Please use responsibly!
"""

import re
import string

# https://stackoverflow.com/questions/241327/remove-c-and-c-comments-using-python
def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def shorten_vars(text):
    # discover template typename identifiers
    pat = '(?:_[A-Z0-9][a-z]+)+'
    tns = sorted(set(re.findall(pat, text)))
    if len(tns) > 26:
        raise ValueError(f'Too many identifiers: {tns}')
    tns = dict(zip(tns, ('_' + c for c in string.ascii_letters)))
    return re.sub(pat, (lambda x:tns[x.group(0)]), text)

def shorten_meta(text):
    tns = {'typename': 'Z', 'monostate': 'Y'}
    pat = '|'.join(tns)
    text = re.sub(pat, (lambda x:tns[x.group(0)]), text)
    for u,v in tns.items():
        text = f'#define {v} {u}\n' + text
    return text

def shorten_nl(text):
    while True:
        new_text = re.sub('\\n\\s*\\n', '\n', text)
        if new_text == text:
            return text
        text = new_text

def main():
    with open('../avl_tree.cpp') as file:
        txt = file.read()
    txt = comment_remover(txt)
    txt = shorten_vars(txt)
    txt = shorten_meta(txt)
    txt = shorten_nl(txt)
    with open('avl_tree_min.cpp', 'w') as file:
        file.write(txt)

if __name__ == '__main__':
    main()

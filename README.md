# xtok
## Описание
Простой графематический анализатор русского языка. Позволяет разбивать текст на токены нескольких типов:
* Слова: вода, tree, Маска, ПрИвЕт, Салтыков-Щедрин
* Знаки пунктуации: ,?!
* Разделители: \t, \n, \s
* Числа: 123, 5, 0213
* Цифробуквенные комплексы: АН512, doom4
* Иероглифы: ツ, 한자
* ASCII-симолы: #
Для каждого из типов токенов определяется собственная графематическая информаця, например регистр для слов, тип пунктуации и разделителя и т.п.

## Сборка
Система сборки взята из открытого проекта Яндекса [catboost](https://github.com/catboost/catboost). Она позволяет собирать статически линкуемые библиотеки и бинарники,
а также делать простые биндинги к python. Чтобы собрать бинарную утилиту:
```
1. ./ya make -r
```
Чтобы собрать и установить wheel для python:
```
1. cd xtok/python-package && python mk_wheel.py
2. sudo pip install xtok-0.1-версия_платформы.whl
```
## Использование
### Бинарник
```
1. cd xtok/tools && ./xtok --json --pretty
Привет!
{
  "tokens":
    [
      {
        "data":"Привет",
        "token_type":"WORD",
        "info":
          [
            "CYRILLIC",
            "CAP_START"
          ]
      },
      {
        "data":"!",
        "token_type":"PUNCT",
        "info":
          [
            "EXCLAMATION_MARK"
          ]
      }
    ]
}
2. cd xtok/tools && ./xtok --input ../data/greenlamp.txt --output tokens.txt #просто с токены с новой строки без информации
```
# python
```python
>>> from xtok import tokenize
>>> tokenize("Привет!")
[{'data': 'Привет', 'type': b'WORD', 'info': [b'CYRILLIC', b'CAP_START']}, {'data': '!', 'type': b'PUNCT', 'info': [b'EXCLAMATION_MARK']}]
```

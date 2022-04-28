import models
import myorm

# mydb 라는 이름을 가진 데이터에비으 생성
mydb = myorm.create_db('mydb')


class Author(myorm.Model):
    # primary key 속성을 가진 id 필드가 포함되어 있어야함
    name = models.CharField(max_length=32)
    email = models.CharField(max_length=128)


# mydb에 author 테이블 생성
Author.create_table(mydb)

author = Author(name='John', email="john@abc.com")
author.save()

del author

# "john@abc.com" 이메일을 가진 author 데이터 선택
# lazy-evaluation 적용 가능 (옵션)
authors = Author.filter(email="john@abc.com")
# ORM이 lazy query evaluation을 지원한다면 첫번째 결과를 가져온다.
# the actual db requested will be made here (실제 db 요청은 여기서 일어난다)
author = authors[0]
assert author.name == 'John'

author.name = 'John Doe'
author.save()  # Update the existing row (해당 row를 Update)
author_id = author.id

del author

author = Author.filter(id=author_id)[0]
print(author.name)  # prints 'John Doe' ('John Doe' 프린트)

안녕하세요 python 사용해서 간단한 자체 orm을 만드는(CRUD) 과제인데 혹시 가능하실까요?

아래 코드에서 사용가능한 myorm.py 를 만드는 일입니다.

```
import myorm

# mydb 라는 이름을 가진 데이터에비으 생성
mydb = myorm.create_db(&#039;mydb&#039;)

class Author(myorm.Model):
# primary key 속성을 가진 id 필드가 포함되어 있어야함
name = models.CharField(max_length=32)
email = models.CharField(max_length=128)

# mydb에 author 테이블 생성
Author.create_table(mydb)

author = Author(name=&#039;John&#039;, email=&quot;john@abc.com&quot;)
author.save()

del author

# &quot;john@abc.com&quot; 이메일을 가진 author 데이터 선택
# lazy-evaluation 적용 가능 (옵션)
authors = Author.filter(email=&quot;john@abc.com&quot;)
# ORM이 lazy query evaluation을 지원한다면 첫번째 결과를 가져온다.
# the actual db requested will be made here (실제 db 요청은 여기서 일어난다)
author = authors[0]
assert author.name == &#039;John&#039;

author.name = &#039;John Doe&#039;
author.save() # Update the existing row (해당 row를 Update)
author_id = author.id

del author

author = Author.filter(id=author_id)[0]
print(author.name) # prints &#039;John Doe&#039; (&#039;John Doe&#039; 프린트)
```

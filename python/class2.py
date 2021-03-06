#coding=utf-8

'''
class Person(object):

    def __init__(self, name, gender):
        self.name = name
        self.gender = gender

class Student(Person):

    def __init__(self, name, gender, score):
        super(Student, self).__init__(name, gender)
        self.score = score

    def __str__(self):
        return '(student: %s , %s ,%s)' % (self.name, self.gender, self.score)
        
    __repr__ = __str__

s = Student('Bob', 'male', 88)
print s
'''
#########################################
'''
class Student(object):

    def __init__(self, name, score):
        self.name = name
        self.score = score

    def __str__(self):
        return '(%s: %s)' % (self.name, self.score)

    __repr__ = __str__

    def __cmp__(self, s):
        if self.score == s.score:
            return cmp(self.name, s.name)
        return -cmp(self.score, s.score)

L = [Student('Tim', 99), Student('Bob', 88), Student('Alice', 99)]
print sorted(L)

p = Student('yuyang', 24)
print p
'''

############################################
'''
class Student(object):
    def __init__(self, *args, **kw):
        self.names = args
        self.others = kw
        for k,v in kw.iteritems():
            setattr(self, k, v)

    def __len__(self):
        return len(self.names)

s = Student('Bob', 'Alice', 'Tim', school="一中")
print len(s)
print s.school
'''

################################

class Fib(object):

    def __init__(self, num):
        a, b, L = 0, 1, []
        for n in range(num):
            L.append(a)
            a, b = b, a + b
        self.numbers = L

    def __str__(self):
        return str(self.numbers)
        
    __repr__ = __str__
    
    def __len__(self):
        return len(self.numbers)

f = Fib(10)
print f
print len(f)


class Fib(object):
    def __init__(self, nums):
        a, b, l = 0, 1, []
        for n in range(nums):
            l.append(a)
            a, b = b, a+b
        self.numbers = l

    def __str__(self):
        return str(self.numbers)

    __repr__ = __str__

    def __len__(self):
        return len(self.numbers)

f = Fib(5)
print f
print len(f)


'''
class Person(object):

    __slots__ = ('name', 'gender')

    def __init__(self, name, gender):
        self.name = name
        self.gender = gender

class Student(Person):

    __slots__ = ('score',)

    def __init__(self, name, gender, score):
        super(Student, self).__init__(name, gender)
        self.score = score

s = Student('Bob', 'male', 59)
s.name = 'Tim'
s.score = 99
print s.score

class Person(object):
    pass

class Student(Person):
    pass

class Teacher(Person):
    pass

class SkillMixin(object):
    pass

class BasketballMixin(SkillMixin):
    def skill(self):
        return 'basketball'

class FootballMixin(SkillMixin):
    def skill(self):
        return 'football'

class BStudent(Student, BasketballMixin):
    pass

class FTeacher(Teacher, FootballMixin):
    pass

s = BStudent()
print s.skill()

t = FTeacher()
print t.skill()
'''
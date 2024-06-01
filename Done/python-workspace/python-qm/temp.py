import string
import random
import RPi.GPIO as GPIO
from PIL import Image, ImageDraw, ImageFont
from schemdraw.parsing import logicparse


inputKeys = 16

GPIO.setmode(GPIO.BCM)
SCLPin = 6
SDOPin = 5

GPIO.setup(SCLPin, GPIO.OUT)
GPIO.setup(SDOPin, GPIO.IN)

keyPressed = 0

def string_to_parser(s):
    s = s.split('+')

    result = ''
    paren_opened = False
    for i in range(len(s)):
        result += '('

        for j in range(len(s[i])):
            if 'A' <= s[i][j] <= 'Z':
                if j < len(s[i]) - 1 and s[i][j + 1] == "'":
                    result += 'not ' + s[i][j]
                else:
                    result += s[i][j]
                if j < len(s[i]) - 1 and not (j == len(s[i]) - 2 and s[i][j + 1] == "'") and not (
                        j == len(s[i]) - 3 and s[i][j + 2] == ')') and not (
                        j == len(s[i]) - 2 and s[i][j + 1] == ')'):
                    if s[i][j + 1] == '(':
                        result += ')'
                    result += ' and '

            if s[i][j] == '(':
                result += s[i][j]
                paren_opened = True
            if s[i][j] == ')':
                result += s[i][j]
                paren_opened = False

        if not paren_opened:
            result += ')'

        if i != len(s) - 1:
            result += ' or '

    return result


def distribute(term, inside_terms):
    distributed_terms = []
    for inside_term in inside_terms:
        distributed_terms.append(term + inside_term)
    return distributed_terms


def remove_bracelet(expr):
    while '(' in expr:
        right_paren_index = expr.index(')')
        left_paren_index = expr.rindex('(', 0, right_paren_index)
        inside = expr[left_paren_index + 1:right_paren_index]
        outside = expr[:left_paren_index].split('+')[-1]

        inside_terms = inside.split('+')
        outside_terms_left = expr[:left_paren_index].split('+')[:-1]
        outside_terms_right = expr[right_paren_index + 1:].split('+')
        del outside_terms_right[0]
        distributed = distribute(outside, inside_terms)

        if len(outside_terms_right) > 0:
            expr = '+'.join(outside_terms_left + distributed + outside_terms_right)
        else:
            expr = '+'.join(outside_terms_left + distributed)

    return expr


def multiply(t1, t2):
    t1 = t1.split('+')
    t2 = t2.split('+')

    prod = ''
    for m in t1:
        temp = ""
        for n in t2:

            if t1.index(m) == len(t1) - 1 and t2.index(n) == len(t2) - 1:
                if m != n:
                    temp = (temp + m + n)
                else:
                    temp += m

            else:
                if m != n:
                    temp = temp + m + n + '+'
                else:
                    temp += m + '+'

        prod += temp

    return prod


def remove_dups(expr):
    expr = expr.split('+')
    new_expr = []

    for term in expr:
        new_term = []
        temp = ''

        for i in range(len(term)):
            if term[i] != "'" and i + 1 < len(term) and term[i + 1] == "'":
                if term[i] in new_term:
                    new_term = []
                    break
                elif term[i] + "'" not in new_term:
                    new_term.append(term[i] + "'")
            elif term[i] != "'" and i + 1 < len(term) and term[i + 1] != "'":
                if term[i] + "'" in new_term:
                    new_term = []
                    break
                elif term[i] not in new_term:
                    new_term.append(term[i])
            elif term[i] != "'" and i == len(term) - 1:
                if term[i] not in new_term:
                    new_term.append(term[i])
            elif term[i] == "'":
                continue

        if len(new_term) != 0:
            new_expr.append(new_term)

    temp_expr = ''
    for ne in new_expr:
        term = ''
        for t in ne:
            term += t
        temp_expr += term + '+'
    return temp_expr[:-1]


def multiply_all(terms):
    prod = terms[0]
    for i in range(1, len(terms)):
        prod = (multiply(terms[i], prod))
    return prod


def reduce_expr(expr):
    reduced = True
    for term in expr:
        matches = [t for t in expr if t != term and len(set(term).intersection(set(t))) == len(term)]
        if (matches):
            reduced = False

    if reduced:
        return expr

    new_expr = []
    temp_expr = expr
    for term in expr:
        matches = [t for t in expr if t != term and len(set(term).intersection(set(t))) == len(term)]
        if (matches):
            new_expr.append(term)
            temp_expr.remove(term)
            for match in matches:
                temp_expr.remove(match)
    expr = reduce_expr(new_expr + temp_expr)

    return expr


def min_len_terms(terms):
    minlen = len(min(terms, key=lambda x: len(x)))
    terms = [term for term in terms if len(term) == minlen]

    return terms


def count_literals(term):
    count = 0
    for char in term:
        if char != "_":
            count += 1

    return count


def fewest_literals(terms):
    min_count = count_literals(min(terms, key=lambda x: count_literals(x)))
    min_lits = []

    for term in terms:
        if count_literals(term) == min_count:
            min_lits.append(term)

    return min_lits


class QM:
    def __init__(self, minterms, chars=[]):
        self.procedure = ""
        minterms = [int(x) for x in minterms]

        self.nbits = len(bin(max(minterms))[2:])
        self.minterms = self.to_binary(minterms)

        self.prime_implicants = []
        self.combined = []
        self.essential_prime_implicants = []
        self.coverage_table = {}
        self.chars = sorted(chars)

    def to_binary(self, minterms=[], nbits=0):
        if nbits:
            mx = nbits
        else:
            mx = self.nbits

        bminterms = []
        for minterm in minterms:
            bstr = bin(minterm)[2:]
            bstr = (mx - len(bstr)) * '0' + bstr
            bminterms.append(bstr)

        return bminterms

    def combine(self, min1, min2):
        if len(min1) != len(min2):
            raise ValueError("Both terms vary in length")
        pos = [i for i in range(len(min1)) if min1[i] != min2[i]]
        if len(pos) == 1:
            i = pos[0]
            return min1[:i] + '_' + min1[i + 1:]

    def combine_groups(self, group1=[], group2=[]):
        result = []
        for mt1 in group1:
            for mt2 in group2:
                offspring = self.combine(mt1, mt2)

                if offspring:

                    self.combined.append(mt1)
                    self.combined.append(mt2)

                    if offspring not in result:
                        result.append(offspring)

        return result

    def combine_generation(self, generation=[]):
        new_gen = []

        for i in range(len(generation) - 1):
            new_group = self.combine_groups(generation[i], generation[i + 1])
            if new_group:
                new_gen.append(new_group)

        return new_gen

    def group_minterms(self, mts=[]):
        mts.sort()
        grps = []

        num_groups = len(mts[0])

        for i in range(num_groups + 1):
            grp = [x for x in mts if x.count('1') == i]

            if grp:
                grps.append(grp)

        for i in range(len(grps)):
            num_ones = grps[i][0].count('1')
            grp = grps[i]

        return grps

    def pis(self):
        mts = self.minterms
        new_gen = self.group_minterms(mts)

        all_gens = [new_gen]
        while new_gen:
            for group in new_gen:
                for term in group:
                    self.prime_implicants.append(term)

            new_gen = self.combine_generation(new_gen)

            if new_gen:
                all_gens.append(new_gen)

        self.prime_implicants = [pi for pi in self.prime_implicants if pi not in self.combined]

        for pi in self.prime_implicants:
            ch = ' (' + self.to_char(pi, self.chars) + ') ' if self.chars else ''
            self.procedure += ('  ' + pi + ch + '\n')

        return self.prime_implicants

    def can_cover(self, pi, minterm):
        pos = [i for i in range(len(pi)) if pi[i] == '_']

        for i in range(len(pi)):
            if i not in pos and pi[i] != minterm[i]:
                return False

        return True

    def primary_epis(self):
        for minterm in self.minterms:
            self.coverage_table[minterm] = []
            for pi in self.prime_implicants:
                if self.can_cover(pi, minterm):
                    self.coverage_table[minterm].append(pi)

        for minterm in self.minterms:
            if len(self.coverage_table[minterm]) == 1:
                self.essential_prime_implicants.append(self.coverage_table[minterm][0])

        self.essential_prime_implicants = list(set(self.essential_prime_implicants))

        self.coverage_table = {k: v for k, v in self.coverage_table.items() if \
                               not set(v).intersection(set(self.essential_prime_implicants))}

        if self.essential_prime_implicants:

            for pi in self.essential_prime_implicants:
                ch = ' (' + self.to_char(pi, self.chars) + ') ' if self.chars else ''
                self.procedure += ('  ' + pi + ch + '\n')

        return self.essential_prime_implicants

    def secondary_epis(self):
        mapvals = list(string.ascii_letters + string.digits)

        mapped = []
        charmap = {}
        prod = []

        for mterm in self.coverage_table:
            strrep = ""
            for t in self.coverage_table[mterm]:
                if t not in mapped:
                    ch = random.choice(mapvals)
                    charmap[ch] = t
                    mapped.append(t)
                    mapvals.remove(ch)
                else:
                    for key in charmap:
                        if t in charmap[key]:
                            ch = key

                if t == self.coverage_table[mterm][-1]:
                    strrep += ch

                else:
                    strrep += ch + '+'
            prod.append(strrep)
        new_prod = []

        if prod:
            prod = multiply_all(prod)
            prod = remove_dups(prod)
            prod = (reduce_expr(prod))
            prod = min_len_terms(prod)
            prod = fewest_literals(prod)

            for t in prod:
                tempstr = ""
                for s in t:
                    ch = self.to_char(charmap[s], self.chars) if self.chars else charmap[s]
                    if s == t[-1]:
                        tempstr += ch
                    else:
                        tempstr += ch + ' + '
                new_prod.append(tempstr)

        return new_prod

    def minimize(self):
        pis = self.pis()

        essential_pi_sol = ""

        primary_epis = self.primary_epis()

        for pi in primary_epis:
            ch = self.to_char(pi, self.chars) if self.chars else pi

            if pi == primary_epis[-1]:
                essential_pi_sol += ch
            else:
                essential_pi_sol += ch + '+'

        secondary_epi_sols = self.secondary_epis()
        possible_solutions = []

        if secondary_epi_sols:
            for spi in secondary_epi_sols:
                if essential_pi_sol:
                    possible_solutions.append(essential_pi_sol + ' + ' + spi)
                else:
                    possible_solutions.append(spi)
        else:
            possible_solutions.append(essential_pi_sol)

        return possible_solutions

    def to_char(self, term, chars):
        i = 0
        res = ''
        for ch in term:
            if ch == '1':
                res += chars[i]

            elif ch == '0':
                res = res + chars[i] + "'"

            i += 1

        return res


if __name__ == "__main__":
    delay_and = 0
    delay_or = 0
    delay_not = 0


    def set_delay(d_and, d_or, d_not):
        global delay_and, delay_or, delay_not

        delay_and = d_and
        delay_or = d_or
        delay_not = d_not


    def has_and(decl):
        return len(decl.replace("'", "")) > 1


    def has_not(decl):
        return "'" in decl


    def get_total_delay(decls):
        delays = []

        for d in decls:
            decl_max = 0

            if has_and(d):
                decl_max += delay_and
            if has_not(d):
                decl_max += delay_not

            delays.append(decl_max)

        return max(delays) + delay_or


    def get_key():
        button = 0
        global keyPressed
        keyState = 0
        time.sleep(0.07)

        for i in range(inputKeys):
            GPIO.output(SCLPin, GPIO.LOW)
            if not GPIO.input(SDOPin):
                keyState = i + 1
            GPIO.output(SCLPin, GPIO.HIGH)

        if keyState > 0 and keyState != keyPressed:
            button = keyState
            keyPressed = keyState
        else:
            keyPressed = keyState
        return button


    def get_keys():
        sop = ""
        keymap = ["A", "B", "C", "D", "+", "'", "(", ")", "<", "enter", "", "", "", "", "", "reset"]

        while True:
            inp = get_key()

            if inp > 0:
                if 1 <= inp <= 8:
                    sop += keymap[inp - 1]
                elif inp == 9:
                    sop = sop[:-1]
                elif inp == 10:
                    print('Input : ' + sop)
                    return sop
                elif inp == 16:
                    sop = ''
                print(sop)

    def get_input():
        sop = get_keys()
        vars = remove_bracelet(sop).split('+')

        variables = []
        for v in vars:
            for i in range(len(v)):
                variables.append(v[i])
        variables = list(set(variables))

        if "'" in variables:
            variables.remove("'")
        if '(' in variables:
            variables.remove("(")
        if ')' in variables:
            variables.remove(")")
        return sop, ','.join(variables)


    expr, variables = get_input()
    sop = remove_dups(remove_bracelet(expr))
    minterms = []

    if sop and variables:
        sop = sop.split('+')
        variables = variables.split(',')
        variables.sort()

        number_list = {}
        for num in range(len(variables) ** 2):
            bin_num = str(bin(num)[2:])
            while len(bin_num) < len(variables):
                bin_num = '0' + bin_num
            number_list[bin_num] = num

        dic = {}
        list_dic = []
        for product in sop:
            for variable in product:
                if ord(variable) in range(65, 123) and product.index(variable) + 1 < len(product) and product[
                    product.index(variable) + 1] == "'":
                    dic[variable] = 0

                elif ord(variable) in range(65, 123):
                    dic[variable] = 1

            list_dic.append(dic)
            dic = {}
        result = []
        for mt in list_dic:
            for num in number_list:
                count = 0
                for i in range(len(variables)):
                    if variables[i] in mt and int(num[i]) == mt[variables[i]]:
                        count += 1
                if len(mt) == count:
                    result.append(number_list[num])
        minterms = list(set(result))

    qm = QM(minterms, variables)
    sols = qm.minimize()
    sols[0] = sols[0]

    print('Before: ' + expr)
    circuit = logicparse(string_to_parser(expr))
    circuit.save('before.svg', False)

    terms = sols[0].split('+')
    terms.sort()
    sol = '+'.join(terms)

    print('After: ' + sol)
    circuit2 = logicparse(string_to_parser(sol))
    circuit2.save('after.svg', False)

    set_delay(18.5, 18.5, 18.5)
    print('\n[Delay]')
    print('\tAND: ' + str(delay_and))
    print('\tOR: ' + str(delay_or))
    print('\tNOT: ' + str(delay_not))

    decls = sols[0].split('+')
    result = get_total_delay(decls)
    print('\nMaximum Delay: ' + str(result))

    before = Image.open('before.png')

    after = Image.open('after.png')

    before2 = before.resize((300, 200))
    after2 = after.resize((300, 200))

    img = Image.new("RGBA", (600, 300), "white")

    img.paste(before2, (0, 50))
    img.paste(after2, (300, 50))

    img_result = ImageDraw.Draw(img)
    font = ImageFont.truetype("Arial.ttf", size=15)
    img_result.text((30, 0), 'Input: ' + expr, (0, 0, 0), font)
    img_result.text((330, 0), 'Output: ' + sol, (0, 0, 0), font)
    img_result.text((30, 250), ('Propagation delay: \n' + str(get_total_delay(expr.split('+'))) + 'ns'), (0, 0, 0),
                    font)
    img_result.text((330, 250), 'Propagation delay: \n' + str(get_total_delay(sol.split('+'))) + 'ns', (0, 0, 0), font)

    img.show()
    img.save('result.png')

    # AB'+B'C(BD+CD')
    # A'B'C'+B'CD'+A'BCD'+AB'C'

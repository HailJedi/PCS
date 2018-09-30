k, n, s, p = map(int, input().split())
one_person_make = n
paper_one_person_need = (one_person_make + s - 1) // s
paper_all_persons_need = paper_one_person_need * k
packs_all_persons_need = (paper_all_persons_need + p - 1) // p
print(packs_all_persons_need)

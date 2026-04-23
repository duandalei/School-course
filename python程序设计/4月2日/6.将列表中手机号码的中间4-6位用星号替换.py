phone = ["18501561234", "13811571314", "15952005358", "13912345678"]


def replace(phone_list):
    new_list = []
    for p in phone_list:
        new_list.append(p[:3] + "****" + p[7:])
    return new_list


phone2 = replace(phone)
print(phone)
print(phone2)

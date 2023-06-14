def find_path(case_id):
    if case_id == 0:
        return []
    next_move = []

    # forward
    total = 0
    line = 1
    while total < case_id:
        total += line * 2 + 1
        line += 1
    mov = 1
    while mov < line:
        next_move.append("Forward")
        mov += 1

    # turn
    line -= 1
    actual_line_size = line * 2 + 1
    case_id = case_id - (total - actual_line_size)
    x = -(actual_line_size) + case_id + (actual_line_size // 2)
    if x < 0:
        next_move.append("Left")
    elif x > 0:
        next_move.append("Right")
    else:
        return next_move

    # forward after turn
    mov = 0
    while mov < abs(x):
        next_move.append("Forward")
        mov += 1

    return next_move

print("find_path(0)", find_path(0))
print("find_path(1)", find_path(1))
print("find_path(2)", find_path(2))
print("find_path(3)", find_path(3))
print("find_path(4)", find_path(4))
print("find_path(5)", find_path(5))
print("find_path(6)", find_path(6))
print("find_path(7)", find_path(7))
print("find_path(8)", find_path(8))
print("find_path(9)", find_path(9))
print("find_path(10)", find_path(10))
print("find_path(11)", find_path(11))
print("find_path(12)", find_path(12))
print("find_path(13)", find_path(13))
print("find_path(14)", find_path(14))
print("find_path(15)", find_path(15))
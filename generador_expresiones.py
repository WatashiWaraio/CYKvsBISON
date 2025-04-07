import random
import string

def random_identifier():
    start = random.choice(string.ascii_letters + '_')
    rest = ''.join(random.choices(string.ascii_letters + string.digits + '_', k=random.randint(0, 6)))
    return start + rest

def random_terminal():
    return random.choice([str(random.randint(1, 100)), random_identifier()])

def random_operator():
    return random.choice(['+', '-', '*', '/'])

def generate_expr_tree(num_ops):
    if num_ops == 0:
        return random_terminal()

    # Ensure at least one operator goes into one side, to avoid empty subtrees
    left_ops = random.randint(0, num_ops - 1)
    right_ops = num_ops - 1 - left_ops

    left_expr = generate_expr_tree(left_ops)
    right_expr = generate_expr_tree(right_ops)
    op = random_operator()

    return f"({left_expr} {op} {right_expr})"

# 🔥 Save each expression as a single line
def save_expressions_to_file(count, filename="expressions"):
    with open(filename, "w") as f:
        expr = generate_expr_tree(count)
        clean_expr = ' '.join(expr.split())
        f.write(clean_expr + '\n')

# ✅ Generate and save expressions
if __name__ == "__main__":
    for i in range(1, 11):
        save_expressions_to_file(filename=f"expressions_{i}.txt", count=1000_000 + 500_000 * i)

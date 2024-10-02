import itertools


# Define a function to generate the combinations and write to a file
def generate_combinations_to_file(n, file_name, sample_size=10):
    # Create the list of numbers
    numbers = list(range(1, n + 1))

    # For each number, we can either use the number itself or its negation (represented as ~x)
    # Both are converted to strings for easier joining later
    choices = [(str(x), f"-{x}") for x in numbers]

    # Get the product of all possible combinations
    combinations = itertools.product(*choices)

    # Open a file for writing
    with open(file_name, "w") as file:
        file.write(f"p cnf {n} {2**n}\n")
        for idx, combo in enumerate(combinations):
            file.write(" ".join(combo) + " 0\n")
            if idx >= sample_size - 1:  # Sample size limit
                break
        file.write("%")


# Generate combinations for numbers from 1 to 1024 and write to a file with a sample size limit
generate_combinations_to_file(
    13, "naive.txt", sample_size=1048576
)  # Adjust sample size as needed

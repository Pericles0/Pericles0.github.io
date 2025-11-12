# Pericles0.github.io
# Aliquot Sequence Calculator

This is a command-line C program designed to compute and display [aliquot sequences](https://en.wikipedia.org/wiki/Aliquot_sequence) for a given starting number. The program can either display the full sequence until it terminates or reaches a specified length, or it can simply return the total length of the sequence. It is optimized to handle large integers (up to 10^15) by using an efficient algorithm based on number theory principles.

## Usage

Run the compiled program from your terminal. It will prompt you for three inputs:

1.  **Starting Number:** The integer to begin the aliquot sequence from (up to 10^15).
2.  **Max Length:** The maximum number of terms to calculate. Enter `0` for an unlimited search.
3.  **Output Preference:**
    *   `f` to print the **full** sequence.
    *   `l` to print only the final **length** of the sequence.

### Mathematical Base:

## (1)[The Fundemental Theorem of arithmetic](https://en.wikipedia.org/wiki/Fundamental_theorem_of_arithmetic)
States that every integer greater than 1 is either prime or can be represented uniquely as a product of prime numbers, up to the order of the factors.
Therefore we can represent each number of the aliquot sequence as a product of primes.
## (2)[Theorem: A composite number n must have a prime factor less than or equal to √n.](https://en.wikipedia.org/wiki/Prime_number#Trial_division)

## The Aliquot Sequence

An aliquot sequence is defined by the recurrence relation:
$s_0 = n$
$s_{k+1} = s(s_k)$

Where $s(n)$ is the **sum of the proper divisors** of $n$ (all divisors of $n$ other than $n$ itself). For example, the proper divisors of 10 are 1, 2, and 5, so $s(10) = 1 + 2 + 5 = 8$. The next term in the sequence is 8.

The sum of proper divisors, $s(n)$, is directly related to the sum of *all* positive divisors, denoted by $\sigma_1(n)$. The relationship is simple:

$$
s(n) = \sigma_1(n) - n
$$

The core of our program is to efficiently calculate $\sigma_1(n)$ for very large numbers.

## The Divisor Function σ₁(n)

As explained in the [Wikipedia article on the Divisor Function](https://en.wikipedia.org/wiki/Divisor_function), if a number $n$ has the prime factorization:

$$
n = p_1^{a_1} p_2^{a_2} \cdots p_k^{a_k}
$$

Then the sum of its divisors, $\sigma_1(n)$, can be calculated with the following formula:

$$
\sigma_1(n) = \prod_{i=1}^{k} \frac{p_i^{a_i+1} - 1}{p_i - 1}
$$

This formula is powerful because it allows us to find the sum of divisors without having to find every single divisor. We only need the prime factors and their exponents. This is the central formula implemented in our code.

### How the Code Works

The program uses two key functions to implement the mathematical logic described above.

### The `SigmaF()` Function

This function calculates $\sigma_1(n)$ directly using the product formula. It works by:
1.  Finding each prime factor $p_i$ of the input number `num`.

To calculate the sum of divisors, we first find the prime factors of the input number.

We only need to search for prime factors up to the square root of the number ($\sqrt{n}$). (Recall theorem (2))
This dramatically limits our search. We implement this check efficiently in our `while` loop by using multiplication instead of a `sqrt()` call:

```c
// This check is equivalent to factor <= sqrt(tmp) but is much faster.
while (factor * factor <= tmp) {
    // ... logic to find exponents of the current factor ...
}


After this loop, if the remaining value of tmp is not 1, then that remaining value must be the final prime factor of the original number. We handle this case immediately after the loop to complete the factorization:
code C

    
// If tmp isn't 1, it's the last prime factor and must be included.
if (tmp != 1) { 
    product *= (tmp + 1); // Incorporate the last prime into the product
}```

This method ensures our prime factorization is fast enough to handle integers up to $10^{15}$.

  
2.  Counting its exponent $a_i$ (stored as `exp` in the code).
3.  Calculating the term $\frac{p_i^{a_i+1} - 1}{p_i - 1}$ for that prime factor.
4.  Multiplying all these terms together into the `product` variable.

This is the key line where the formula is implemented:

```c
// Corresponds to the term (p^(a+1) - 1) / (p - 1)
product *= (OverflFactor - 1) / (factor - 1);
```

However, for very large numbers, the intermediate calculation of $p_i^{a_i+1}$ can cause an overflow. The `Aliquotf()` function uses a more robust method to handle this.

### The `Aliquotf()` Function:

The `Aliquotf()` function calculates the next term in the sequence, $s(n) = \sigma_1(n) - n$. To avoid the overflow issues of a direct `SigmaF(n)` calculation, it leverages a key property of the divisor function: **it is multiplicative**.

This means that if you have two coprime numbers, $m$ and $k$, then $\sigma_1(m \cdot k) = \sigma_1(m) \cdot \sigma_1(k)$.

The prime power components of a number's factorization ($p_1^{a_1}$, $p_2^{a_2}$, etc.) are all coprime to each other. Therefore, we can express $\sigma_1(n)$ as:

$$
\sigma_1(n) = \sigma_1(p_1^{a_1}) \cdot \sigma_1(p_2^{a_2}) \cdots \sigma_1(p_k^{a_k})
$$

This is  what the `Aliquotf()` function does:
1. It finds each prime power component ($p_i^{a_i}$) of the input number `num`.
2. For each component, it calls `SigmaF()` to calculate its sum of divisors. For example, `SigmaF(P(factor, exp))` calculates $\sigma_1(p_i^{a_i})$. This is safe because the component is much smaller than the original number `num`.
3. It multiplies these results together to get the final $\sigma_1(n)$.

```c
// Calculate σ₁(pᵢ^ᵃᵢ) for one prime power component
unsigned long long SigmaF_P_factor = SigmaF(P(factor, exp));

// Multiply it into the total product: σ₁(n) = σ₁(p₁^ᵃ¹) * σ₁(p₂^ᵃ²) * ...
product *= SigmaF_P_factor;
```
4. Finally, it subtracts the original number to get the sum of proper divisors:

```c
// Returns σ₁(n) - n
return (product - num);
```
This method avoids large intermediate calculations, allowing the program to handle numbers up to 10^15 without overflow.



# Deep Learning

Deep Learning is one of the most common Machine Learning algorithms. Imagine that every AI problem can be resume as a complex algebraic formula. All inputs are used as parameters of a formula that calculate the probability of all outputs.

So let's suppose the probability of women getting pregnant. What input can we use? Age, previous pregnancy and being married can all be variables of this formula. But we don't know the formula, we only know the facts. So let's do some math? Imagine that A is the age of the woman, B is the number of previous pregnancies and C is the fact she is married. We imagine that these are relevant variables to calculate the probability of a woman getting pregnant.

> **Warning**
>
> This is not a valid model and this is can be an unethical model depending on your usage.

```
Age                → A
Previous pregnance → B
Being married      → C

a · A + b · B + c · C = P
```

So we don't know the value for `a`, `b` and `c`. But we can suppose that these are functions, so let's rewrite to:

```
fa(A) + fb(B) + fc(C) = P
```

This is difficult to calculate! But what if we reduce this function to inputs and one output? We have the perceptron.

![Perceptron](/docs/README/images/perceptron.png)

The perceptron is a function that receives some parameters, a function and we calculate the output. It is based on the neuron where each input is represented by the signal received by the dendrites and the output is represented by the signal output by the axon.

![Neuron](/docs/README/images/neuron.png)

So how can we model a neuron with code?

```cpp
Perceptron andPerceptron({10, 10, -15});
boolean p00 = andPerceptron.run({0, 0}); // ~0
boolean p01 = andPerceptron.run({0, 1}); // ~0
boolean p10 = andPerceptron.run({1, 0}); // ~0
boolean p11 = andPerceptron.run({1, 1}); // ~1


Perceptron orPerceptron({15, 15, -10});
boolean p00 = orPerceptron.run({0, 0}); // ~0
boolean p01 = orPerceptron.run({0, 1}); // ~1
boolean p10 = orPerceptron.run({1, 0}); // ~1
boolean p11 = orPerceptron.run({1, 1}); // ~1
```
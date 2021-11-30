# Normalization

To increase performance of a NN all values should be normalize to be inside the interval of [0.0,1.0]. For this library we do not expect that the user know how to normalize the data, so we automatically normalize it. To avoid normalization problems, we create a struct to hold the normalization rule that we apply to the data. This information can be used to normalize and denormalize the data.

We have 3 kinds of normalization:

* INTEGER
* FLOATING_POINT
* ENUM
* BOOLEAN


## Integer
The interger normalization follow the formula

![Integer normalization](http://www.latex2png.com/pngs/8060a675e694a03915a89c50c40fd955.png)

## Floating Point
The float point normalization follow the formula

![Integer normalization](http://www.latex2png.com/pngs/8060a675e694a03915a89c50c40fd955.png)

## Enum

Assume that `dict` is all values used in the normalization process. If `x` can be found in `dict` we translate it to the `index + 1` and normalize it avoid `0.0`. `0.0` will be used to values not found on `dict`.

## Boolean

Boolean values follow the same logic from Enum. This means that true values are `True`, `TRUE`, `t` or the last sorted value. Otherwise false.
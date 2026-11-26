# Mathematical foundations

## Integer vectors

For vectors \(x,y\in\mathbb{Z}^n\), the standard inner product is

\[
\langle x,y\rangle=\sum_{i=1}^{n}x_i y_i.
\]

The squared Euclidean norm is

\[
\|x\|^2=\langle x,x\rangle.
\]

We store the squared norm because it is an integer and avoids introducing square roots.

## Exact rational numbers

A rational is represented as \(p/q\), where \(p,q\in\mathbb{Z}\), \(q>0\), and \(\gcd(|p|,q)=1\). Every arithmetic operation restores this canonical representation.

## Unimodular transformations

An integer matrix \(U\in\mathbb{Z}^{n\times n}\) is unimodular when

\[
\det(U)\in\{-1,+1\}.
\]

Its inverse is also an integer matrix. Consequently, multiplying a lattice basis by a unimodular matrix changes the basis but not the lattice it generates.

## Bareiss determinant algorithm

The determinant implementation uses fraction-free Gaussian elimination. At elimination step \(k\), each trailing entry is updated by

\[
a_{ij}^{(k+1)}=
\frac{a_{kk}^{(k)}a_{ij}^{(k)}
-a_{ik}^{(k)}a_{kj}^{(k)}}{a_{k-1,k-1}^{(k-1)}}.
\]

The divisor is exact under the Bareiss algorithm's invariant. This controls intermediate fraction growth compared with ordinary rational Gaussian elimination.

// http://spfrnd.de/posts/2018-03-10-fast-exponential.html

template<typename Real, size_t degree, size_t i = 0>
struct ExpApprox {
    static Real evaluate(Real x) {
        //constexpr Real c = 1.0 / static_cast<Real>(1u << degree);
        x = ExpApprox<Real, degree, i + 1>::evaluate(x);
        return x * x;
    }
};

template<typename Real, size_t degree>
struct ExpApprox<Real, degree, degree> {
    static Real evaluate(Real x) {
        constexpr Real c = 1.0 / static_cast<Real>(1u << degree);
        x = 1.0 + c * x;
        return x;
    }
};


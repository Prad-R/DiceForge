#ifndef DF_CUSTOM_DISTRIBUTION_H
#define DF_CUSTOM_DISTRIBUTION_H

#include "distribution.h"
#include "types.h"
#include <vector>
#include <functional>

namespace DiceForge {
    /// @brief DiceForge::CustomDistribution - Samples a continuous pdf, cutomised by the user 
    /// @note The CustomDistribution class assumes that the inputted probability density function (PDF) is a valid PDF over the specified range.
    /// @note Users are responsible for ensuring that the provided PDF satisfies the necessary conditions, such as non-negativity and integrability over the defined domain 
    using PDF_Function = std::function<real_t(real_t)>;

    class CustomDistribution : public Continuous {
    private:
        real_t lower_limit;
        real_t upper_limit;
        std::vector<std::pair<real_t, real_t>> cdf_values; // (input, cdf)
        PDF_Function pdf_function; // Declare pdf_function as a member variable

    public:
        CustomDistribution(real_t lower, real_t upper, PDF_Function pdf);

        real_t next(real_t r);
        
        /// @brief Returns the expected value of the distribution
        /// @note The expectation value is approximate
        real_t expectation() const override final;
        
        /// @brief Returns the variance of the distribution
        /// @note The variance is an approximatation 
        real_t variance() const override final;

        /// @brief Returns the minimum possible value of the random variable described by the distribution
        real_t minValue() const override final;

        /// @brief Returns the maximum possible value of the random variable described by the distribution
        real_t maxValue() const override final;

        /// @brief Probabiliity density function (pdf) of the distribution
        /// @param x location where the pdf is to be evaluated
        real_t pdf(real_t x) const override final;

        /// @brief Cummalative density function (cdf) of the distribution
        /// @param x location where the pdf is to be evaluated
        /// @note Nymerical methods of inegration are emplyed to find the cdf value. This does not ensure that the function itslef is integrable over the given range.
        real_t cdf(real_t x) const override final;
    };
} // namespace DiceForge

#endif // DF_CUSTOM_DISTRIBUTION_H



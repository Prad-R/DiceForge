#ifndef DF_GENERATORS_H
#define DF_GENERATORS_H

#include "diceforge_core.h"

namespace DiceForge
{
    /**
     * @brief DiceForge::BlumBlumShub32 - A RNG utilizing the Blum-Blum-Shub algorithm
     * for generating 32-bit unsigned random integers
     */
    class BlumBlumShub32 : public Generator<uint32_t>
    {
        private:
            static const uint64_t p = 60539;
            static const uint64_t q = 50147;
            static const uint64_t n = p * q;

            uint64_t state; // Internal state

            /**
             * @brief propagate - Advances the internal state using the Blum-Blum-Shub algorithm
             */
            inline void propagate();

            /**
             * @brief generate - Generates a random number using the Blum-Blum-Shub algorithm
             * @return The generated random number
             */
            uint32_t generate() override;

            /**
             * @brief check_seed - Checks if the seed is coprime with n (p*q)
             * @note If it is not then a constant is added to the seed to make it coprime
             * @param seed The seed value
             */
            void check_seed(uint32_t& seed);

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed The new seed value
             */
            void reseed(uint32_t seed) override;

        public:
            /**
             * @brief Constructor for BlumBlumShub32
             * @param seed The initial seed value
             */
            BlumBlumShub32(uint32_t seed){
                check_seed(seed);
            }

            /**
             * @brief Destructor for BlumBlumShub32
             */
            ~BlumBlumShub32() = default;
    };

    /**
     * @brief DiceForge::BlumBlumShub64 - A RNG utilizing the Blum-Blum-Shub algorithm
     * for generating 64-bit unsigned random integers
     */
    class BlumBlumShub64 : public Generator<uint64_t>
    {
        private:
            static const uint64_t p = 60539;
            static const uint64_t q = 50147;
            static const uint64_t n = p * q;

            uint64_t state; // Internal state

            /**
             * @brief propagate - Advances the internal state using the Blum-Blum-Shub algorithm
             */
            inline void propagate();

            /**
             * @brief generate - Generates a random number using the Blum-Blum-Shub algorithm
             * @return The generated random number
             */
            uint64_t generate() override;

            /**
             * @brief check_seed - Checks if the seed is coprime with n (p*q)
             * @note If it is not then a constant is added to the seed to make it coprime
             * @param seed The seed value
             */
            void check_seed(uint64_t& seed);

            /**
             * @brief reseed - Reseeds the generator with a new seed
             * @param seed The new seed value
             */
            void reseed(uint64_t seed) override;

        public:
            /**
             * @brief Constructor for BlumBlumShub64
             * @param seed The initial seed value
             */
            BlumBlumShub64(uint64_t seed){
                check_seed(seed);
            }

            /**
             * @brief Destructor for BlumBlumShub64
             */
            ~BlumBlumShub64() = default;
    };

    /// @brief DiceForge::LFSR64 - Linear Feedback Shift Register class (derived from Generator)
    /// for generating 64-bit unsigned integers
    class LFSR64 : public DiceForge::Generator<uint64_t> {
    private:
        // Two curr_seeds, together forming a 128-bit seed
        uint64_t curr_seed1 = 0, curr_seed2 = 0;
        // Function to generate a random 64-bit positive integer
        uint64_t generate() override;
        // Function to reseed the RNG
        void reseed(uint64_t seed) override;
    public:
        /// @brief Initializes the LFSR with the specified seed
        /// @param seed seed to initialize the RNG with
        LFSR64(uint64_t seed);
        /// @brief Default destructor
        ~LFSR64() = default;
    };

    /// @brief DiceForge::LFSR32 - Linear Feedback Shift Register class (derived from Generator)
    /// for generating 32-bit unsigned integers
    class LFSR32 : public DiceForge::Generator<uint32_t> {
    private:
        // Two curr_seeds, together forming a 128-bit seed
        uint64_t curr_seed1 = 0, curr_seed2 = 0;
        // Function to generate a random 32-bit positive integer
        uint32_t generate() override;
        // Function to reseed the RNG
        void reseed(uint32_t seed) override;
    public:    
        /// @brief Initializes the LFSR with the specified seed
        /// @param seed seed to initialize the RNG with
        LFSR32(uint32_t seed);
        /// @brief Default destructor
        ~LFSR32() = default;
    };

    /// @brief DiceForge::MT32 - A Mersenne Twister RNG for generating 32-bit unsigned integers
    class MT32 : public Generator<uint32_t>
    {
    private:
        // Main Parameters:
        int N;                          // length of state value vector
        int M;                          // optimum value as mid
        uint32_t A;                     // vector in the matrix A
        uint32_t upperbits, lowerbits;  // for obtaining first w-r bits of the number
        // Tempering Parameters:
        uint32_t tempering_mask_B;
        uint32_t tempering_mask_C;
        uint32_t tempering_shift_U;
        uint32_t tempering_shift_S;
        uint32_t tempering_shift_T;
        uint32_t tempering_shift_L;
        // Other Parameters:
        std::vector<uint32_t> mt;       // State Vector
        int mti = N + 1;                // Used as index for the array MT.
        uint32_t seed;                  // Seed given from main
        // Functions to generate first N pseudo-random numbers as a seed for the algorithm.
        void sgenrand(uint32_t);
        void trytransform();
        uint32_t temper(uint32_t);
        uint32_t generate() override;
        void reseed(uint32_t seed) override;
    public:
        /// @brief Initializes the Mersenne Twister RNG with the specified seed
        /// @param seed seed to initialize the RNG with
        MT32(uint32_t seed);
        ~MT32() = default;
    };
    
    /// @brief DiceForge::MT64 - A Mersenne Twister RNG for generating 64-bit unsigned integers
    class MT64 : public Generator<uint64_t>
    {
    private:
        // Main Parameters:
        int N;                          // length of state value vector
        int M;                          // optimum value as mid
        uint64_t A;                     // vector in the matrix A
        uint64_t upperbits, lowerbits;  // for obtaining first w-r bits of the number
        // Tempering Parameters:
        uint64_t tempering_mask_B;
        uint64_t tempering_mask_C;
        uint64_t tempering_shift_U;
        uint64_t tempering_shift_S;
        uint64_t tempering_shift_T;
        uint64_t tempering_shift_L;
        // Other Parameters:
        std::vector<uint64_t> mt;       // State Vector
        int mti = N + 1;                // Used as index for the array MT.
        uint64_t seed;                  // Seed given from main
        // Functions to generate first N pseudo-random numbers as a seed for the algorithm.
        void sgenrand(uint64_t);
        void trytransform();
        uint64_t temper(uint64_t);
        uint64_t generate() override;
        void reseed(uint64_t seed) override;
    public:
        /// @brief Initializes the Mersenne Twister RNG with the specified seed
        /// @param seed seed to initialize the RNG with
        MT64(uint64_t seed);
        ~MT64() = default;
    };
            
    /// @brief DiceForge::NaorReingold - An implementation of the Naor-Reingold PRF 
    /// for generating 32-bit unsigned integers
    class NaorReingold : public Generator<uint32_t> {
        private:
            uint32_t m_state;   // Internal state
            uint32_t generate() override;
            void reseed(uint32_t seed) override;        
        public:
            /// @brief Initializes the PRF with the given seed
            /// @param seed seed to initialize the PRF with
            /// @note The key for the PRF is predetermined and fixed. The seed is not the key.
            NaorReingold(uint32_t seed);
            /// @brief Default destructor
            ~NaorReingold() = default;
    };

    typedef NaorReingold NaorReingold32;


    /// @brief DiceForge::XORShift32 - A PRNG following the XORShift* algorithm
    /// A naive implementation of the original XORShift algorithm proposed by Marsaglia
    /// followed by a multiplicative transform
    /// @note Generates 32-bit unsigned integers
    class XORShift32 : public Generator<uint32_t>
    {
    private:
        uint32_t m_state;   // Internal state
        uint32_t generate() override;
        void reseed(uint32_t seed) override;
    public:
        /// @brief Initializes the XOR Shift RNG with the specified seed
        /// @param seed must be a non-zero number
        /// @note If the given seed is zero, then the current system is used as the seed
        XORShift32(uint32_t seed);
        /// @brief Default destructor
        ~XORShift32() = default;
    };

    /// @brief DiceForge::XORShift64 - A PRNG following the XORShift* algorithm
    /// A naive implementation of the original XORShift algorithm proposed by Marsaglia
    /// followed by a multiplicative transform
    /// @note Generates 64-bit unsigned integers
    class XORShift64 : public Generator<uint64_t>
    {
    private:
        uint64_t m_state;   // Internal state
        uint64_t generate() override;
        void reseed(uint64_t seed) override;
    public:
        /// @brief Initializes the XOR Shift RNG with the specified seed
        /// @param seed must be a non-zero number
        /// @note If the given seed is zero, then the current system is used as the seed
        XORShift64(uint64_t seed);
        /// @brief Default destructor
        ~XORShift64() = default;
    };

    // Typedefs for convenience

    typedef BlumBlumShub64 BlumBlumShub;
    typedef LFSR64 LFSR;
    typedef MT64 MT;
    typedef NaorReingold NaorReingold32;
    typedef XORShift64 XORShift;

} // namespace DiceForge


#endif
add_library(distributions STATIC
        NormalDistribution.cpp
        UniformDistribution.cpp
        ExponentialDistribution.cpp
        CauchyDistribution.cpp
        LaplaceDistribution.cpp
        BernoulliDistribution.cpp
        BinomialDistribution.cpp
        GeometricDistribution.cpp
        PoissonDistribution.cpp
        DistributionExperiment.cpp
        ../markov-chain/MarkovChain.cpp
        ../markov-chain/MarkovChain.hpp
        ../markov-chain/MarkovTextModel.cpp
        ../markov-chain/MarkovTextModel.hpp
)
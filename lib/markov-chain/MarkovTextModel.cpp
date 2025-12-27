#include "MarkovTextModel.hpp"

namespace ptm {

    void MarkovTextModel::TrainFromText(const std::string& text) {
        chain_.Train(Tokenize(text));
    }

    std::string MarkovTextModel::GenerateText(std::size_t num_tokens, std::mt19937& rng, const std::string& start_token) const {
        std::string start = start_token;
        if (start == ""){
            if (chain_.States().empty()){
                return "";
            }

            start = chain_.States()[0];
        }

        return Detokenize(chain_.Generate(start, num_tokens, rng));
    }

    const MarkovChain& MarkovTextModel::Chain() const noexcept {
        return chain_;
    }

    std::vector<std::string> MarkovTextModel::Tokenize(const std::string& text) const {
        std::vector<MarkovChain::State> tokens = std::vector<MarkovChain::State>();

        if (level_ == TokenLevel::Word) {
            std::stringstream ss(text);
            std::string word;

            while (ss >> word) {
                tokens.push_back(word);
            }
        } else {
            for(auto c : text){
                std::string s = "";
                s.push_back(c);
                tokens.push_back(s);
            }
        }

        return tokens;
    }

    std::string MarkovTextModel::Detokenize(const std::vector<std::string>& tokens) const {
        std::string text = "";

        if (level_ == TokenLevel::Word) {
            for (auto token : tokens) { 
                text += token + " ";
            }
    
            text.pop_back();
        } else {
            for (auto token : tokens) { 
                text += token;
            }
        }
        

        return text;
    }
}
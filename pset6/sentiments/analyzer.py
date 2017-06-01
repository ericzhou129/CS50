import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """
        Initialize Analyzer.
        Load positive and negative words
        """
        # initialize the file path variables
        self.positives = positives # let positives and negatives be the file names 
        self.negatives = negatives
        
        # initialize lists
        self.positive_list = []
        self.negative_list = []
            
        # Store positive and negative words into lists
        # (omit any leading or trailing whitespace using str.strip)
        # (don't include comments with str.startswith)
        
        f_positives = open(self.positives, "r")
        for line in f_positives: # for each line in the positive file (automatically iterates over each line)
            if line.startswith(';') == False: # if the line is not comment
                striped_line = line.strip()
                self.positive_list.append(line.strip()) # strip each word of white space and append to list
                
        f_negatives = open(self.negatives, "r")
        for line in f_negatives:
            if line.startswith(';') == False: # if the line is not comment
                self.negative_list.append(line.strip()) # strip each word of white space and append to list
        
        # print(self.positive_list)        
        # for word in self.negative_list:
        #     print(word)
        

        
    def analyze(self, text):
        """
        Analyze text for sentiment, returning its score.
        Assign each word in text a value (-1,0,1)
        Calculate text's total score
        """
        # Tokenize the text (split into list of words)
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        # Iterate over tokens
        # Check if word is positive or negatives
        # Return score
        # (Note: in this algorithm, the positive, negative, neutral rating of a statement is 
        # purely depedant on the amount of positive or negative words. )
        
        total_score = 0
        result = 0
        
        for word in tokens:
            if word.lower() in self.positive_list:
                result = 1
            elif word.lower() in self.negative_list:
                result = -1
            else:
                result = 0
            
            total_score += result
        
        # print(tokens)
        # print(total_score)
        
        return total_score

        

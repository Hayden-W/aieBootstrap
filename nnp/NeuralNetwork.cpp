#include "inc/NeuralNetwork.h"
#include <random>
#include <time.h>
#include <assert.h>
NeuralNetwork::NeuralNetwork(int I_N, int H_N, int O_N) :
	m_inputNodeCount(I_N), m_hiddenNodeCount(H_N), m_outputNodeCount(O_N)
{
	AssignWeights();
	/*
	Fill all the vectors here so we dont have to mess with memory every time we train the network
	*/
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		m_hiddenLayerSum.push_back(0.0);
		m_hiddenLayerResult.push_back(0.0);
		m_hiddenLayerDerivative.push_back(0.0);
	}

	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_outputLayerSum.push_back(0.0);
		m_outputLayerResult.push_back(0.0);
		m_outputNodeError.push_back(0.0);
		m_outputLayerDerivative.push_back(0.0);
	}
}

double NeuralNetwork::Sigmoid(double input)
{
	return 1 / (1 + exp(-input));
}

void NeuralNetwork::AssignWeights()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < ((m_inputNodeCount + 1) * m_hiddenNodeCount) + ((m_hiddenNodeCount + 1) * m_outputNodeCount); i++)
	{
		int randNum = rand() % 2;
		if (randNum == 1)
			m_weights.push_back(-1 * (double(rand()) / (double(RAND_MAX) + 1.0))); // generate number between -1.0 and 0.0
		else
			m_weights.push_back(double(rand()) / (double(RAND_MAX) + 1.0)); // generate number between 1.0 and 0.0

		m_gradients.push_back(0.0); //Fill our gradients here, to save on proccesses later.
		m_weightUpdate.push_back(0.0);
		m_previousWeightUpdate.push_back(0.0);
		m_weightCount++;
	}
}

std::vector<double> NeuralNetwork::Train(std::vector<double> inputData, std::vector<double> resultData)
{
	/*TODO: 
	Calculate hidden layers                                   [x]
	Calculate output neurons based on hidden layers			  [x]
	calculate the error of the output compared to resultData  [x]
	calculate the derivatives of the neurons				  [x]
	Calculate the gradient									  [x]
	Update the weights										  [x]
	^ get all that from the neural_net.cpp             
	GLHF
	*/

	if (inputData.size() != m_inputNodeCount)
	{
		assert(!!false || "Input data vector is not the right size! (too many / too few input nodes)");
	}

	/*
	For each hidden node, multiply the input nodes by their weights to get its sum, then add
	the bias multiplied by its weight to get the full sum, and then sigmoid that to get 
	the hidden node's result to give to the output layer.
	*/

	m_currentWeight = 0;
	m_errorPercent = 0.0;
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		m_hiddenLayerSum[i] = 0.0;
		for (int x = 0; x < m_inputNodeCount; x++)
		{
			m_hiddenLayerSum[i] += inputData[x] * m_weights[m_currentWeight++];
		}
		m_hiddenLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_hiddenLayerResult[i] = Sigmoid(m_hiddenLayerSum[i]); //calculate the output value of this node

		//Reset the derivative for later, this is a bit gross, however it saves a fair few proccesses
		m_hiddenLayerDerivative[i] = 0.0;
	}
	/*
	Calculate each output node's value based on the value of the hidden nodes that was 
	calculated above.
	*/
	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_outputLayerSum[i] = 0.0;
		for (int x = 0; x < m_hiddenNodeCount; x++)
		{
			m_outputLayerSum[i] += m_hiddenLayerResult[x] * m_weights[m_currentWeight++];
		}
		m_outputLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_outputLayerResult[i] = Sigmoid(m_outputLayerSum[i]); //Calculate output value of this node

		m_outputNodeError[i] = m_outputLayerResult[i] - resultData[i]; //calulate the error of this output
		// ^ add the difference between this node's output and its expected output to the error count
	}
	
	/*
	Calculate the derivatives for the output nodes based on thier sum and the error percent.
	*/
	for (int i = 0 ; i < m_outputNodeCount; i++)
	{
		m_outputLayerDerivative[i] = -m_outputNodeError[i] * (exp(m_outputLayerSum[i]) / pow((1 + exp(m_outputLayerSum[i])), 2));
	}

	/*
	Calculate the derivatives for the hidden nodes based on thier sum and the output node derivative.
	*/
	int currentWeightPos = m_hiddenNodeCount * (m_inputNodeCount + 1); //Go to the weight between the first hidden node and the first output node
	
	for (int x = 0; x < m_outputNodeCount; x++)
	{	
		for (int i = 0; i < m_hiddenNodeCount; i++)
		{
			m_hiddenLayerDerivative[i] += (exp(m_hiddenLayerSum[i]) / pow((1 + exp(m_hiddenLayerSum[i])), 2)) * m_weights[currentWeightPos++] * m_outputLayerDerivative[x];
		}
		currentWeightPos++; //Skip the bias
	}

	/*
	Calculate the gradient of the weights based on the derivatives of the nodes.
	*/
	m_currentGradient = 0;
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		for (int x = 0; x < m_inputNodeCount; x++)
		{
			m_gradients[m_currentGradient++] = Sigmoid(inputData[x]) * m_hiddenLayerDerivative[i];
		}
		m_gradients[m_currentGradient++] = Sigmoid(m_bias) * m_hiddenLayerDerivative[i];
	}

	for (int i = 0; i < m_outputNodeCount; i++)
	{
		for (int x = 0; x < m_hiddenNodeCount; x++)
		{
			m_gradients[m_currentGradient++] = m_hiddenLayerResult[x] * m_outputLayerDerivative[i];
		}
		m_gradients[m_currentGradient++] = Sigmoid(m_bias) * m_outputLayerDerivative[i];
	}

	/*
	Calculate the updates to the weights and apply said updates
	*/
	for (int i = 0; i < m_weightCount; i++)
	{
		m_weightUpdate[i] = (m_learningRate * m_gradients[i]) + (m_momentum * m_previousWeightUpdate[i]);
		m_previousWeightUpdate[i] = m_weightUpdate[i];

		m_weights[i] += m_weightUpdate[i];
	}
	m_errorPercent = 0.0;
	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_errorPercent += m_outputNodeError[i];
	}

	return m_outputLayerResult;
}

void NeuralNetwork::SelfTrain(std::vector<double> inputData, bool correct)
{
	if (inputData.size() != m_inputNodeCount)
	{
		assert(!!false || "Input data vector is not the right size! (too many / too few input nodes)");
	}

	/*
	For each hidden node, multiply the input nodes by their weights to get its sum, then add
	the bias multiplied by its weight to get the full sum, and then sigmoid that to get
	the hidden node's result to give to the output layer.
	*/

	m_currentWeight = 0;
	m_errorPercent = 0.0;
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		m_hiddenLayerSum[i] = 0.0;
		for (int x = 0; x < m_inputNodeCount; x++)
		{
			m_hiddenLayerSum[i] += inputData[x] * m_weights[m_currentWeight++];
		}
		m_hiddenLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_hiddenLayerResult[i] = Sigmoid(m_hiddenLayerSum[i]); //calculate the output value of this node

		//Reset the derivative for later, this is a bit gross, however it saves a fair few proccesses
		m_hiddenLayerDerivative[i] = 0.0;
	}
	/*
	Calculate each output node's value based on the value of the hidden nodes that was
	calculated above.
	*/
	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_outputLayerSum[i] = 0.0;
		for (int x = 0; x < m_hiddenNodeCount; x++)
		{
			m_outputLayerSum[i] += m_hiddenLayerResult[x] * m_weights[m_currentWeight++];
		}
		m_outputLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_outputLayerResult[i] = Sigmoid(m_outputLayerSum[i]); //Calculate output value of this node
		//This training method doesn't have a correct %, because there is nothing to compare it to.
	}

	/*
	Calculate the derivatives for the output nodes based on thier sum and wether the prediction of the network was correct
	*/
	for (int i = 0; i < m_outputNodeCount; i++)
	{


		//                              \/ that might have to be changed to a positive value
		if (correct)
		{
			//m_outputLayerDerivative[i] =  0.007 * (exp(m_outputLayerSum[i]) / pow((1 + exp(m_outputLayerSum[i])), 2));
		}
		else
		{
			m_outputLayerDerivative[i] =  -1.0 * (exp(m_outputLayerSum[i]) / pow((1 + exp(m_outputLayerSum[i])), 2));
		}

		/*
		This self learning algorithm wont work for this case because all the weights recieve the same change, causing them to all eventually become the same value
		and stopping an obvious selection from rising from the bunch, it would be useful if it could target individual strains of nodes connected to a single output, 
		but unfortunatley it cannot :(
		*/
		
		//Either step towards or away from this answer, depending on wether this onput data generated a correct result
	}

	/*
	Calculate the derivatives for the hidden nodes based on thier sum and the output node derivative.
	*/

	int currentWeightPos = m_hiddenNodeCount * (m_inputNodeCount + 1); //Go to the weight between the first hidden node and the first output node

	for (int x = 0; x < m_outputNodeCount; x++)
	{
		for (int i = 0; i < m_hiddenNodeCount; i++)
		{
			m_hiddenLayerDerivative[i] += (exp(m_hiddenLayerSum[i]) / pow((1 + exp(m_hiddenLayerSum[i])), 2)) * m_weights[currentWeightPos++] * m_outputLayerDerivative[x];
		}
		currentWeightPos++; //Skip the bias
	}

	/*
	Calculate the gradient of the weights based on the derivatives of the nodes.
	*/
	m_currentGradient = 0;
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		for (int x = 0; x < m_inputNodeCount; x++)
		{
			m_gradients[m_currentGradient++] = Sigmoid(inputData[x]) * m_hiddenLayerDerivative[i];
		}
		m_gradients[m_currentGradient++] = Sigmoid(m_bias) * m_hiddenLayerDerivative[i];
	}

	for (int i = 0; i < m_outputNodeCount; i++)
	{
		for (int x = 0; x < m_hiddenNodeCount; x++)
		{
			m_gradients[m_currentGradient++] = m_hiddenLayerResult[x] * m_outputLayerDerivative[i];
		}
		m_gradients[m_currentGradient++] = Sigmoid(m_bias) * m_outputLayerDerivative[i];
	}

	/*
	Calculate the updates to the weights and apply said updates
	*/
	for (int i = 0; i < m_weightCount; i++)
	{
		m_weightUpdate[i] = (m_learningRate * m_gradients[i]) + (m_momentum * m_previousWeightUpdate[i]);
		m_previousWeightUpdate[i] = m_weightUpdate[i];

		m_weights[i] += m_weightUpdate[i];
	}
}

std::vector<double> NeuralNetwork::Test(std::vector<double> inputData)
{
	if (inputData.size() != m_inputNodeCount)
	{
		assert(!!false || "Input data vector is not the right size! (too many / too few input nodes)");
	}

	m_currentWeight = 0;
	m_errorPercent = 0.0;
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		m_hiddenLayerSum[i] = 0.0;
		for (int x = 0; x < m_inputNodeCount; x++)
		{
			m_hiddenLayerSum[i] += inputData[x] * m_weights[m_currentWeight++];
		}
		m_hiddenLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_hiddenLayerResult[i] = Sigmoid(m_hiddenLayerSum[i]); //calculate the output value of this node

															   //Reset the derivative for later, this is a bit gross, however it saves a fair few proccesses
		m_hiddenLayerDerivative[i] = 0.0;
	}
	/*
	Calculate each output node's value based on the value of the hidden nodes that was
	calculated above.
	*/
	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_outputLayerSum[i] = 0.0;
		for (int x = 0; x < m_hiddenNodeCount; x++)
		{
			m_outputLayerSum[i] += m_hiddenLayerResult[x] * m_weights[m_currentWeight++];
		}
		m_outputLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_outputLayerResult[i] = Sigmoid(m_outputLayerSum[i]); //Calculate output value of this node
	}
	return m_outputLayerResult;
}

double NeuralNetwork::TrainAndReturnAvgOutputDelta(std::vector<double> inputData, std::vector<double> resultData)
{
	/*TODO:
	Calculate hidden layers                                   [x]
	Calculate output neurons based on hidden layers			  [x]
	calculate the error of the output compared to resultData  [x]
	calculate the derivatives of the neurons				  [x]
	Calculate the gradient									  [x]
	Update the weights										  [x]
	^ get all that from the neural_net.cpp
	GLHF
	*/

	if (inputData.size() != m_inputNodeCount)
	{
		assert(!!false || "Input data vector is not the right size! (too many / too few input nodes)");
	}

	/*
	For each hidden node, multiply the input nodes by their weights to get its sum, then add
	the bias multiplied by its weight to get the full sum, and then sigmoid that to get
	the hidden node's result to give to the output layer.
	*/

	m_currentWeight = 0;
	m_errorPercent = 0.0;
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		m_hiddenLayerSum[i] = 0.0;
		for (int x = 0; x < m_inputNodeCount; x++)
		{
			m_hiddenLayerSum[i] += inputData[x] * m_weights[m_currentWeight++];
		}
		m_hiddenLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_hiddenLayerResult[i] = Sigmoid(m_hiddenLayerSum[i]); //calculate the output value of this node

															   //Reset the derivative for later, this is a bit gross, however it saves a fair few proccesses
		m_hiddenLayerDerivative[i] = 0.0;
	}
	/*
	Calculate each output node's value based on the value of the hidden nodes that was
	calculated above.
	*/
	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_outputLayerSum[i] = 0.0;
		for (int x = 0; x < m_hiddenNodeCount; x++)
		{
			m_outputLayerSum[i] += m_hiddenLayerResult[x] * m_weights[m_currentWeight++];
		}
		m_outputLayerSum[i] += m_bias * m_weights[m_currentWeight++]; //Add bias
		m_outputLayerResult[i] = Sigmoid(m_outputLayerSum[i]); //Calculate output value of this node

		m_outputNodeError[i] = m_outputLayerResult[i] - resultData[i]; //calulate the error of this output
																	  // ^ add the difference between this node's output and its expected output to the error count
	}

	/*
	Calculate the derivatives for the output nodes based on thier sum and the error percent.
	*/
	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_outputLayerDerivative[i] = -m_outputNodeError[i] * (exp(m_outputLayerSum[i]) / pow((1 + exp(m_outputLayerSum[i])), 2));
	}

	/*
	Calculate the derivatives for the hidden nodes based on thier sum and the output node derivative.
	*/
	int currentWeightPos = m_hiddenNodeCount * (m_inputNodeCount + 1); //Go to the weight between the first hidden node and the first output node

	for (int x = 0; x < m_outputNodeCount; x++)
	{
		for (int i = 0; i < m_hiddenNodeCount; i++)
		{
			m_hiddenLayerDerivative[i] += (exp(m_hiddenLayerSum[i]) / pow((1 + exp(m_hiddenLayerSum[i])), 2)) * m_weights[currentWeightPos++] * m_outputLayerDerivative[x];
		}
		currentWeightPos++; //Skip the bias
	}

	/*
	Calculate the gradient of the weights based on the derivatives of the nodes.
	*/
	m_currentGradient = 0;
	for (int i = 0; i < m_hiddenNodeCount; i++)
	{
		for (int x = 0; x < m_inputNodeCount; x++)
		{
			m_gradients[m_currentGradient++] = Sigmoid(inputData[x]) * m_hiddenLayerDerivative[i];
		}
		m_gradients[m_currentGradient++] = Sigmoid(m_bias) * m_hiddenLayerDerivative[i];
	}

	for (int i = 0; i < m_outputNodeCount; i++)
	{
		for (int x = 0; x < m_hiddenNodeCount; x++)
		{
			m_gradients[m_currentGradient++] = m_hiddenLayerResult[x] * m_outputLayerDerivative[i];
		}
		m_gradients[m_currentGradient++] = Sigmoid(m_bias) * m_outputLayerDerivative[i];
	}

	/*
	Calculate the updates to the weights and apply said updates
	*/
	for (int i = 0; i < m_weightCount; i++)
	{
		m_weightUpdate[i] = (m_learningRate * m_gradients[i]) + (m_momentum * m_previousWeightUpdate[i]);
		m_previousWeightUpdate[i] = m_weightUpdate[i];

		m_weights[i] += m_weightUpdate[i];
	}

	m_errorPercent = 0.0;
	for (int i = 0; i < m_outputNodeCount; i++)
	{
		m_errorPercent += m_outputNodeError[i];
	}
	m_errorPercent /= m_outputNodeCount;

	for (unsigned int i = 0; i < resultData.size(); i++)
	{
		if (resultData[i] > 0.9)
		{
			return m_outputLayerResult[i];
		}
	}

	return m_errorPercent;
}

std::vector<double> NeuralNetwork::GetWeights()
{
	return m_weights;
}

void NeuralNetwork::setWeights(std::vector<double> newWeights)
{
	if(newWeights.size() == m_weights.size())
		m_weights = newWeights;
}

void NeuralNetwork::reweightNN()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < ((m_inputNodeCount + 1) * m_hiddenNodeCount) + ((m_hiddenNodeCount + 1) * m_outputNodeCount); i++)
	{
		int randNum = rand() % 2;
		if (randNum == 1)
			m_weights[i] = (-1 * (double(rand()) / (double(RAND_MAX) + 1.0))); // generate number between -1.0 and 0.0
		else
			m_weights[i] = (double(rand()) / (double(RAND_MAX) + 1.0)); // generate number between 1.0 and 0.0

		m_gradients[i] = (0.0); //Fill our gradients here, to save on proccesses later.
		m_weightUpdate[i] = (0.0);
		m_previousWeightUpdate[i] = (0.0);
	}
}

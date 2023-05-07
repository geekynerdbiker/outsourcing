import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import convolve2d
from skimage.transform import resize
from skimage.filters import gabor_kernel


### Step 1: Encoding the input image as spikes ###

# set time steps to 1001
timesteps = 1001

# read image
input_image = plt.imread('lena.jpg')
# remove color channel, gray-scaling
input_image = resize(input_image, (512, 512))[:, :, 0] / 255.0

# spike firing rate a
spike_firing_rate = input_image * 100
# a * delta t
spike_probability = spike_firing_rate * 0.001
# make spike map
spike_map = np.random.poisson(lam=spike_probability, size=(timesteps, 512, 512))


### Step 2: Convolution of the spike map using the Gabor kernel ###

# set sigma x, sigma y, k, theta
sigma, k, theta = 2, 1, np.pi / 2
# init gabor kernel filter
gabor_kernel = gabor_kernel(sigma_x=sigma, sigma_y=sigma, frequency=k, theta=theta)
# init filtered spikes np array
filtered_spikes = np.zeros((timesteps, 32, 32))
# int each time steps
for i in range(timesteps):
    # create convolution
    convolved = convolve2d(spike_map[i], gabor_kernel)
    # convolve by 32 x 32 filter
    filtered_spikes[i] = convolved[:32, :32]


### Step 3: Evaluation of synaptic current over time ###

# time constant for synaptic current decay
tau_s = 0.02
# weights for synapse model
w = gabor_kernel
# resize w to match synaptic_current
w = resize(w, (32, 32))
# init synaptic current np array
synaptic_current = np.zeros((1001, 32, 32))
# array saver for each 1ms
time = np.arange(timesteps)[:, None, None]

synaptic_current = np.sum(filtered_spikes[:timesteps-1] * w * np.exp(-time[1:] / (tau_s * 1000)), axis=0)


### Step 4: Evaluation of membrane potential over time ###

# membrane potential time constant
tau_m = 0.04
# resistance of leakage channel
R = 1
# resting potential
u_rest = 0
# spiking threshold
u_th = 0.05
# init membrane potential np array
membrane_potential = np.zeros((timesteps, 32, 32))
# init spike train np array
spike_train = np.zeros((timesteps, 32, 32))

# in each time steps
for i in range(1, timesteps):
    # do calculate each membrane potential
    membrane_potential[i] = membrane_potential[i - 1] * np.exp(-1 / (tau_m * 1000)) + synaptic_current[i] / R + u_rest
    # do calculate each spike train
    spike_train[i] = np.where(membrane_potential[i] >= u_th, 1, 0)
    # find same potenial value where u rest value is same as spike train
    membrane_potential[i] = np.where(spike_train[i] == 1, u_rest, membrane_potential[i])

### Step 5: Evaluation of spike-count rate over the layer ###

# calculate size of spikes
spike_count_rate = np.sum(spike_train, axis=0)
# print image
plt.imshow(spike_count_rate, cmap='hot')
plt.show()
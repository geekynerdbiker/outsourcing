import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def awgn_(input, dB_snr):
    snr = 10 ** (dB_snr / 10)
    signal_power = 1
    awgn_power = signal_power / snr
    awgn_power_tensor = torch.tensor(awgn_power, dtype=torch.float32)
    awgn = torch.sqrt(awgn_power_tensor / 2) * (
            torch.randn_like(input, dtype=torch.float32) + 1j * torch.randn_like(input, dtype=torch.float32)
    )
    return input + awgn


def ber(orig, pred):
    orig = orig.view(-1).numpy()
    pred = np.array([int(p, 2) for p in pred])
    err = (orig != pred).sum()
    return err / len(orig)


def plot(snr, ber):
    plt.figure(figsize=(8, 6))
    plt.semilogy(snr, ber, marker="o", linestyle="-", linewidth=2, markersize=8)
    plt.title("BER vs SNR")
    plt.xlabel("SNR (dB)")
    plt.ylabel("BER")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.minorticks_on()
    plt.show()


def eval_plot(model, test, labels, snr_range):
    b_vals = []
    for s in snr_range:
        c_test = test[:, 0] + 1j * test[:, 1]
        noisy = awgn_(c_test, s)
        r = noisy.real
        i = noisy.imag
        noisy_tensor = torch.stack([r.clone().detach(), i.clone().detach()], dim=1)
        model.eval()
        with torch.no_grad():
            preds = model(noisy_tensor)
            _, preds = torch.max(preds, 1)
        bits = [format(p.item(), "02b") for p in preds]
        labels = labels.view(-1, 1)
        b_vals.append(ber(labels, bits))
    plot(snr_range, b_vals)


def modulate_qpsk(bits):
    if len(bits) % 2 != 0:
        raise ValueError("Length of bits must be even.")
    bit_pairs = np.array(bits).reshape(-1, 2)
    mapping = {
        (0, 0): 1 + 1j,
        (0, 1): -1 + 1j,
        (1, 1): -1 - 1j,
        (1, 0): 1 - 1j
    }
    symbols = np.array([mapping[tuple(pair)] for pair in bit_pairs])
    return symbols


def plot_constellation(symbols):
    plt.figure(figsize=(6, 6))
    plt.scatter(symbols.real, symbols.imag, color='red')
    plt.axhline(0, color='gray', linestyle='--')
    plt.axvline(0, color='gray', linestyle='--')
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.xlim(-2, 2)
    plt.ylim(-2, 2)
    plt.show()


class QPSKModel(nn.Module):
    def __init__(self):
        super(QPSKModel, self).__init__()
        self.fc1 = nn.Linear(2, 8)
        self.fc2 = nn.Linear(8, 16)
        self.fc3 = nn.Linear(16, 4)
        self.drop = nn.Dropout(0.75)
        self.act = nn.LeakyReLU()

    def forward(self, x):
        x = self.act(self.fc1(x))
        x = self.drop(self.act(self.fc2(x)))
        x = self.fc3(x)
        return x


class AutoEncoder(nn.Module):
    def __init__(self):
        super(AutoEncoder, self).__init__()

        # Encoder
        self.encoder = nn.Sequential(
            nn.Linear(2, 256),
            nn.LeakyReLU(0.1),
            nn.Linear(256, 128),
            nn.LeakyReLU(0.1),
            nn.Linear(128, 2),
            nn.BatchNorm1d(2)
        )

        # Decoder
        self.decoder = nn.Sequential(
            nn.Linear(2, 128),
            nn.LeakyReLU(0.1),
            nn.Linear(128, 256),
            nn.LeakyReLU(0.1),
            nn.Linear(256, 2)
        )

    def forward(self, x):
        latent = self.encoder(x)
        reconstructed = self.decoder(latent)
        return reconstructed


def prob1():
    train = pd.read_csv("./data/tr_qpsk.csv", header=None)
    train[0] = train[0].str.replace("i", "j")
    train_c = train[0].apply(lambda x: complex(x))
    train_r = train_c.apply(lambda x: x.real)
    train_i = train_c.apply(lambda x: x.imag)
    train_d = np.loadtxt("./data/tr_dec.csv", delimiter=",")
    train = pd.DataFrame({"r": train_r, "i": train_i, "d": train_d})

    test = pd.read_csv("./data/te_qpsk.csv", header=None)
    test[0] = test[0].str.replace("i", "j")
    test_c = test[0].apply(lambda x: complex(x))
    test_r = test_c.apply(lambda x: x.real)
    test_i = test_c.apply(lambda x: x.imag)
    test_d = np.loadtxt("./data/te_dec.csv", delimiter=",")
    test = pd.DataFrame({"r": test_r, "i": test_i, "d": test_d})

    x_train = torch.tensor(train[["r", "i"]].values, dtype=torch.float32)
    y_train = torch.tensor(train[["d"]].values, dtype=torch.long).squeeze()
    x_test = torch.tensor(test[["r", "i"]].values, dtype=torch.float32)
    y_test = torch.tensor(test[["d"]].values, dtype=torch.long).squeeze()

    epochs = 5
    batch = 64
    lr = 0.0001

    model = QPSKModel()
    loss_fn = nn.CrossEntropyLoss()
    opt = optim.Adam(model.parameters(), lr=lr)

    for e in range(epochs):
        model.train()
        total_loss = 0

        for i in range(0, len(x_train), batch):
            x_b = x_train[i: i + batch]
            y_b = y_train[i: i + batch]

            opt.zero_grad()
            out = model(x_b)

            loss = loss_fn(out, y_b)
            loss.backward()
            opt.step()
            total_loss += loss.item()
            _, preds = torch.max(out, 1)

        print(f"Epoch {e + 1}/{epochs}, Loss: {total_loss:.4f}")

    model.eval()

    snr_vals = range(0, 11)
    eval_plot(model, x_test, y_test, snr_vals)


def prob2():
    bits = [0, 0, 0, 1, 1, 1, 1, 0]
    symbols = modulate_qpsk(bits)
    plot_constellation(symbols)

    train = pd.read_csv("./data/tr_qpsk.csv", header=None)
    train[0] = train[0].str.replace("i", "j")
    train_c = train[0].apply(lambda x: complex(x))
    train_r = train_c.apply(lambda x: x.real)
    train_i = train_c.apply(lambda x: x.imag)
    train_d = np.loadtxt("./data/tr_dec.csv", delimiter=",")
    train = pd.DataFrame({"r": train_r, "i": train_i, "d": train_d})

    test = pd.read_csv("./data/te_qpsk.csv", header=None)
    test[0] = test[0].str.replace("i", "j")
    test_c = test[0].apply(lambda x: complex(x))
    test_r = test_c.apply(lambda x: x.real)
    test_i = test_c.apply(lambda x: x.imag)
    test_d = np.loadtxt("./data/te_dec.csv", delimiter=",")
    test = pd.DataFrame({"r": test_r, "i": test_i, "d": test_d})

    x_train = torch.tensor(train[["r", "i"]].values, dtype=torch.float32)
    y_train = torch.tensor(train[["d"]].values, dtype=torch.long).squeeze()
    x_test = torch.tensor(test[["r", "i"]].values, dtype=torch.float32)
    y_test = torch.tensor(test[["d"]].values, dtype=torch.long).squeeze()

    epochs = 5
    batch = 64
    lr = 0.0001

    model = QPSKModel()
    loss_fn = nn.CrossEntropyLoss()
    opt = optim.Adam(model.parameters(), lr=lr)

    for e in range(epochs):
        model.train()
        total_loss = 0

        for i in range(0, len(x_train), batch):
            x_b = x_train[i: i + batch]
            y_b = y_train[i: i + batch]
            opt.zero_grad()
            out = model(x_b)
            loss = loss_fn(out, y_b)
            loss.backward()
            opt.step()
            total_loss += loss.item()
            _, preds = torch.max(out, 1)

        print(f"Epoch {e + 1}/{epochs}, Loss: {total_loss:.4f}")

    snr_vals = range(0, 11)
    eval_plot(model, x_test, y_test, snr_vals)


def prob3():
    train = pd.read_csv("./data/tr_qpsk.csv", header=None)
    train[0] = train[0].str.replace("i", "j")
    train_c = train[0].apply(lambda x: complex(x))
    train_r = train_c.apply(lambda x: x.real)
    train_i = train_c.apply(lambda x: x.imag)
    train_d = np.loadtxt("./data/tr_dec.csv", delimiter=",")
    train = pd.DataFrame({"r": train_r, "i": train_i, "d": train_d})

    test = pd.read_csv("./data/te_qpsk.csv", header=None)
    test[0] = test[0].str.replace("i", "j")
    test_c = test[0].apply(lambda x: complex(x))
    test_r = test_c.apply(lambda x: x.real)
    test_i = test_c.apply(lambda x: x.imag)
    test_d = np.loadtxt("./data/te_dec.csv", delimiter=",")
    test = pd.DataFrame({"r": test_r, "i": test_i, "d": test_d})

    x_train = torch.tensor(train[["r", "i"]].values, dtype=torch.float32)
    x_test = torch.tensor(test[["r", "i"]].values, dtype=torch.float32)
    y_test = torch.tensor(test[["d"]].values, dtype=torch.long).squeeze()

    epochs = 10
    batch = 128
    lr = 0.00001

    model = AutoEncoder()
    loss_fn = nn.MSELoss()
    opt = optim.Adam(model.parameters(), lr=lr)

    for e in range(epochs):
        model.train()
        total_loss = 0

        for i in range(0, len(x_train), batch):
            x_b = x_train[i:i + batch]
            opt.zero_grad()

            encoded = model.encoder(x_b)
            noisy_encoded = awgn_(torch.complex(encoded[:, 0], encoded[:, 1]), 20)
            noisy_real = noisy_encoded.real
            noisy_imag = noisy_encoded.imag
            noisy_tensor = torch.stack([noisy_real, noisy_imag], dim=1)
            reconstructed = model.decoder(noisy_tensor)

            loss = loss_fn(reconstructed, x_b)
            loss.backward()
            opt.step()
            total_loss += loss.item()

        print(f"Epoch {e + 1}/{epochs}, Loss: {total_loss:.4f}")

    snr_vals = range(0, 11)
    eval_plot(model, x_test, y_test, snr_vals)


if __name__ == '__main__':
    while True:
        print('1: Deep Learning Decoder with files')
        print('2: Deep Learning Decoder with Generated Bits')
        print('3: Autoencoder with Generated Bits')
        print('0: Quit')
        command = input("\n$ ")

        if command == 1:
            print('Running Deep Learning Decoder with files...')
            prob1()
        elif command == 2:
            print('Deep Learning Decoder with Generated Bits...')
            prob2()

        elif command == 3:
            print('Running Autoencoder with Generated Bits...')
            prob3()

        elif command == 0:
            print('Quit Program...')
            break

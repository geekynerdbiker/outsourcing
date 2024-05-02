import pandas as pd
import numpy as np
from rectpack import newPacker

import os
import matplotlib.pyplot as plt
import matplotlib.patches as patches


def getAB(T: int, L: int, H: int):
    if T > L:
        if L > H:
            return np.array([max(T, L, H), L])
        else:
            if T > H:
                return np.array([max(T, L, H), H])
            else:
                return np.array([max(T, L, H), T])
    else:
        if T > H:
            return np.array([max(T, L, H), T])
        else:
            if L > H:
                return np.array([max(T, L, H), H])
            else:
                return np.array([max(T, L, H), L])


def _save_board(packer, board_number, figure_path):
    bid = board_number - 1
    board = packer[bid]
    x = board.width
    y = board.height

    fig = plt.figure()
    ax = fig.add_subplot(111, aspect='equal')

    ax.set_xlim(0, x)
    ax.set_ylim(0, y)

    # ax.grid()

    for rect in board:
        ax.add_patch(
            patches.Rectangle(
                (rect.x, rect.y),  # (x,y)
                rect.width,  # width
                rect.height,  # height
                edgecolor='black'
            )
        )

        center_x = rect.x + 0.5 * rect.width
        center_y = rect.y + 0.5 * rect.height
        plt.text(rect.x, rect.y, rect.rid)
        plt.gca().axes.xaxis.set_visible(False)
        plt.gca().axes.yaxis.set_visible(False)

    fig.savefig(figure_path, dpi=90, bbox_inches='tight')


def save_boards(packer, number, type):
    board_number = 1
    while True:
        if type == 'norm':
            figure_path = os.path.join('result/norm_bin_%s.png' % number)
        elif type == 'big':
            figure_path = os.path.join('result/big_bin_%s.png' % number)
        try:
            _save_board(packer, board_number=board_number,
                        figure_path=figure_path)
        except IndexError as e:
            break

        board_number += 1


# Load data from excel files
parts_df = pd.read_excel('230401_NE_RHD.xlsx', sheet_name='FD4')
bins_df = pd.read_excel('bins_RHD.xlsx', sheet_name='FD4')

print(parts_df)
print(bins_df)

# Filter parts and bins by classification
big_parts_df = parts_df.loc[parts_df['CLASSIFICATION'] == 'big']
norm_parts_df = parts_df.loc[parts_df['CLASSIFICATION'] == 'norm']
big_bins_df = bins_df.loc[bins_df['CLASSIFICATION'] == 'big']
norm_bins_df = bins_df.loc[bins_df['CLASSIFICATION'] == 'norm']

print(big_parts_df)

print(norm_parts_df)

print(big_bins_df)

print(norm_bins_df)

# Define dimensions of bins
big_bins_dim = big_bins_df[['T', 'L']].to_numpy()
norm_bins_dim = norm_bins_df[['T', 'L']].to_numpy()

# Define dimensions of parts
big_parts_dim = big_parts_df[['T', 'L', 'H']].to_numpy()
norm_parts_dim = norm_parts_df[['T', 'L', 'H']].to_numpy()

# Define names of parts
big_parts_names = big_parts_df['P/NAME'].to_numpy()
norm_parts_names = norm_parts_df['P/NAME'].to_numpy()

# T, L, H -> A, B
big_parts_dim_temp = np.zeros((len(big_parts_dim), 2), int)
norm_parts_dim_temp = np.zeros((len(norm_parts_dim), 2), int)

for i in range(len(big_parts_dim)):
    big_parts_dim_temp[i] = getAB(big_parts_dim[i][0], big_parts_dim[i][1], big_parts_dim[i][2])

for i in range(len(norm_parts_dim)):
    norm_parts_dim_temp[i] = getAB(norm_parts_dim[i][0], norm_parts_dim[i][1], norm_parts_dim[i][2])

big_parts_dim = big_parts_dim_temp
norm_parts_dim = norm_parts_dim_temp

# Define packing sequence
big_bins_seq = big_bins_df['NO'].to_numpy()
norm_bins_seq = norm_bins_df['NO'].to_numpy()
big_parts_seq = big_parts_df['NO'].to_numpy()
norm_parts_seq = norm_parts_df['NO'].to_numpy()

# Check if all parts were packed

# Get the number of parts that were packed
num_norm_parts_packed = 0
num_big_parts_packed = 0

# Get the number of bins that were packed
num_norm_bins_packed = 0
num_big_bins_packed = 0

# Pack norm parts into all available bins
norm_idx, norm_end, norm_number = 0, 0, 0
for i, dim in enumerate(norm_bins_dim):
    packed = False
    norm_packer = newPacker()
    norm_rect_ids = {}
    norm_packer.add_bin(*dim)
    for j in range(len(norm_parts_dim)):
        if norm_idx >= len(norm_parts_dim):
            break
        norm_rect_ids[norm_packer.add_rect(*norm_parts_dim[norm_idx], rid=norm_parts_names[norm_idx])] = norm_parts_seq[
            norm_idx]
        norm_packer.pack()

        norm_end = len(norm_packer.rect_list())
        if j + 1 != norm_end:
            norm_idx -= norm_end
            norm_packer = newPacker()
            norm_rect_ids = {}
            norm_packer.add_bin(*dim)
            for k in range(norm_end):
                norm_rect_ids[norm_packer.add_rect(*norm_parts_dim[norm_idx + k], rid=norm_parts_names[norm_idx + k])] = \
                    norm_parts_seq[
                        norm_idx + k]
            norm_packer.pack()
            num_norm_parts_packed += len(norm_packer.rect_list())
            save_boards(norm_packer, norm_number, 'norm')
            norm_number += 1
            packed = True
            norm_idx += norm_end
            break

        norm_idx += 1
    if packed is False:
        save_boards(norm_packer, norm_number, 'big')
        norm_number += 1
    num_norm_bins_packed += 1

# Pack big parts into big bins
big_idx, big_end, big_number = 0, 0, 0
for i, dim in enumerate(big_bins_dim):
    packed = False
    big_packer = newPacker()
    big_rect_ids = {}
    big_packer.add_bin(*dim)

    for j in range(len(big_parts_dim) + len(norm_parts_dim[norm_idx:])):
        if j < len(big_parts_dim):
            big_rect_ids[big_packer.add_rect(*big_parts_dim[big_idx], rid=big_parts_names[big_idx])] = big_parts_seq[
                big_idx]
            big_packer.pack()

            big_end = len(big_packer.rect_list())
            if j + 1 != big_end:
                big_idx -= big_end
                big_packer = newPacker()
                big_rect_ids = {}
                big_packer.add_bin(*dim)
                for k in range(big_end):
                    big_rect_ids[big_packer.add_rect(*big_parts_dim[big_idx + k], rid=big_parts_names[big_idx + k])] = \
                        big_parts_seq[
                            big_idx + k]
                    num_big_parts_packed += 1
                big_packer.pack()
                save_boards(big_packer, big_number, 'big')
                big_number += 1
                packed = True
                big_idx += big_end
                break
            big_idx += 1
        else:
            if norm_idx >= len(norm_parts_dim):
                break
            big_rect_ids[big_packer.add_rect(*norm_parts_dim[norm_idx], rid=norm_parts_names[norm_idx])] = \
                norm_parts_seq[
                    norm_idx]
            big_packer.pack()

            big_end = len(big_packer.rect_list())
            if j + 1 != big_end:
                big_idx -= big_end
                big_packer = newPacker()
                big_rect_ids = {}
                big_packer.add_bin(*dim)
                for k in range(big_end):
                    if norm_idx + k >= len(norm_parts_dim):
                        break
                    big_rect_ids[
                        big_packer.add_rect(*norm_parts_dim[norm_idx + k], rid=norm_parts_names[norm_idx + k])] = \
                        norm_parts_seq[
                            norm_idx + k]
                    num_norm_parts_packed += 1
                big_packer.pack()
                save_boards(big_packer, big_number, 'big')
                big_number += 1
                packed = True
                norm_idx += big_end
                break
            norm_idx += 1

    if packed is False:
        num_big_parts_packed += len(big_packer.rect_list())
        save_boards(big_packer, big_number, 'big')
        big_number += 1
    num_big_bins_packed += 1

num_parts_packed = num_norm_parts_packed + num_big_parts_packed
num_bins_packed = num_norm_bins_packed + num_big_bins_packed

# Get the total number of parts
num_norm_parts_total = len(norm_parts_df)
num_big_parts_total = len(big_parts_df)
num_parts_total = num_norm_parts_total + num_big_parts_total

# Get the total number of bins
num_norm_bins_total = len(norm_bins_df)
num_big_bins_total = len(big_bins_df)
num_bins_total = num_norm_bins_total + num_big_bins_total

# Print the results
print("Number of parts packed: ", num_parts_packed, " out of ", num_parts_total)
if (num_parts_total > num_parts_packed):
    print('Packing Failed')
else:
    print('Packing Success')

print('사용된 일반부품 개수 : ' + str(num_norm_parts_packed) + '개')
print('사용된 대부품 개수 : ' + str(num_big_parts_packed) + '개')
print('사용된 총부품 개수 : ' + str(num_parts_packed) + '개')
print('사용된 중박스 개수 : ' + str(num_norm_bins_packed) + '개')
print('사용된 대박스 개수 : ' + str(num_big_bins_packed) + '개')
print('사용된 총박스 개수 : ' + str(num_bins_packed) + '개')

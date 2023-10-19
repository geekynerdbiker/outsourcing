import torch
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

netNetwork = None

# 그라디언트 컴퓨팅 사용하지 않음
torch.set_grad_enabled(False)
# cudnn 사용
torch.backends.cudnn.enabled = True

# 네트워크 모델 클래스
class Network(torch.nn.Module):
    def __init__(self):
        super().__init__()

        self.netVggOne = torch.nn.Sequential(
            torch.nn.Conv2d(in_channels=3, out_channels=64, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False)
        )

        self.netVggTwo = torch.nn.Sequential(
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
            torch.nn.Conv2d(in_channels=64, out_channels=128, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=128, out_channels=128, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False)
        )

        self.netVggThr = torch.nn.Sequential(
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
            torch.nn.Conv2d(in_channels=128, out_channels=256, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=256, out_channels=256, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=256, out_channels=256, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False)
        )

        self.netVggFou = torch.nn.Sequential(
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
            torch.nn.Conv2d(in_channels=256, out_channels=512, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False)
        )

        self.netVggFiv = torch.nn.Sequential(
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
            torch.nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False),
            torch.nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(inplace=False)
        )

        self.netScoreOne = torch.nn.Conv2d(in_channels=64, out_channels=1, kernel_size=1, stride=1, padding=0)
        self.netScoreTwo = torch.nn.Conv2d(in_channels=128, out_channels=1, kernel_size=1, stride=1, padding=0)
        self.netScoreThr = torch.nn.Conv2d(in_channels=256, out_channels=1, kernel_size=1, stride=1, padding=0)
        self.netScoreFou = torch.nn.Conv2d(in_channels=512, out_channels=1, kernel_size=1, stride=1, padding=0)
        self.netScoreFiv = torch.nn.Conv2d(in_channels=512, out_channels=1, kernel_size=1, stride=1, padding=0)

        self.netCombine = torch.nn.Sequential(
            torch.nn.Conv2d(in_channels=5, out_channels=1, kernel_size=1, stride=1, padding=0),
            torch.nn.Sigmoid()
        )

        self.load_state_dict({strKey.replace('module', 'net'): tenWeight for strKey, tenWeight in
                              torch.hub.load_state_dict_from_url(
                                  url='http://content.sniklaus.com/github/pytorch-hed/network-' + 'bsds500' + '.pytorch',
                                  file_name='hed-' + 'bsds500').items()})

    def forward(self, tenInput):
        tenInput = tenInput * 255.0
        tenInput = tenInput - torch.tensor(data=[104.00698793, 116.66876762, 122.67891434], dtype=tenInput.dtype,
                                           device=tenInput.device).view(1, 3, 1, 1)

        tenVggOne = self.netVggOne(tenInput)
        tenVggTwo = self.netVggTwo(tenVggOne)
        tenVggThr = self.netVggThr(tenVggTwo)
        tenVggFou = self.netVggFou(tenVggThr)
        tenVggFiv = self.netVggFiv(tenVggFou)

        tenScoreOne = self.netScoreOne(tenVggOne)
        tenScoreTwo = self.netScoreTwo(tenVggTwo)
        tenScoreThr = self.netScoreThr(tenVggThr)
        tenScoreFou = self.netScoreFou(tenVggFou)
        tenScoreFiv = self.netScoreFiv(tenVggFiv)

        tenScoreOne = torch.nn.functional.interpolate(input=tenScoreOne, size=(tenInput.shape[2], tenInput.shape[3]),
                                                      mode='bilinear', align_corners=False)
        tenScoreTwo = torch.nn.functional.interpolate(input=tenScoreTwo, size=(tenInput.shape[2], tenInput.shape[3]),
                                                      mode='bilinear', align_corners=False)
        tenScoreThr = torch.nn.functional.interpolate(input=tenScoreThr, size=(tenInput.shape[2], tenInput.shape[3]),
                                                      mode='bilinear', align_corners=False)
        tenScoreFou = torch.nn.functional.interpolate(input=tenScoreFou, size=(tenInput.shape[2], tenInput.shape[3]),
                                                      mode='bilinear', align_corners=False)
        tenScoreFiv = torch.nn.functional.interpolate(input=tenScoreFiv, size=(tenInput.shape[2], tenInput.shape[3]),
                                                      mode='bilinear', align_corners=False)

        return self.netCombine(torch.cat([tenScoreOne, tenScoreTwo, tenScoreThr, tenScoreFou, tenScoreFiv], 1))


def estimate(tenInput):
    global netNetwork

    if netNetwork is None:
        netNetwork = Network().cuda().eval()

    intWidth = tenInput.shape[2]
    intHeight = tenInput.shape[1]

    return netNetwork(tenInput.cuda().view(1, 3, intHeight, intWidth))[0, :, :, :].cpu()


def edge_detection(img, mask1, mask2, threshold):
    # 이미지 shape 및 마스크를 통한 필터 크기 설정
    img_shape = img.shape
    filter_size = mask1.shape

    # 이미지 shape 및 필터 사이즈를 토대로 결과 shape 생성
    result_shape = tuple(np.array(img_shape) - np.array(filter_size) + 1)

    # x, y 마스크를 따로 적용하기 위해 두개의 결과 생성
    result1 = np.zeros(result_shape)
    result2 = np.zeros(result_shape)

    for h in range(0, result_shape[0]):
        for w in range(0, result_shape[1]):
            # 모든 이미지 픽셀 좌표에 대해 x, y 마스크 결과 개별 저장
            tmp = img[h:h + filter_size[0], w:w + filter_size[1]]
            result1[h, w] = np.abs(np.sum(tmp * mask1))
            result2[h, w] = np.abs(np.sum(tmp * mask2))

    # x + y 결과 한 이미지로 합산
    result = result1 + result2

    # thresholding 값을 통해 결과 갱신
    thr_result = np.zeros(result_shape)
    thr_result[result > threshold] = 1

    # 결과 반환
    return result1, result2, result, thr_result


# 테스트용 이미지.
img = Image.open('lena.png').convert('L')
img = np.array(img)

# 소벨 x, y 마스크 각각 선언
sobel_x = np.array([[-1, 0, 1],
                    [-2, 0, 2],
                    [-1, 0, 1]])

sobel_y = np.array([[1, 2, 1],
                    [0, 0, 0],
                    [-1, -2, -1]])

# 엣지 검출 수행
sobel, nms, thr, bt = edge_detection(img, sobel_x, sobel_y, threshold=140)

# 결과 저장 - Sobel Mask
plt.imshow(sobel)
plt.savefig('./lena_sobel.png')

# 결과 저장 - Sobel Mask NMS
plt.imshow(nms)
plt.savefig('./lena_sobel_nms.png')

# 결과 저장 - Sobel Mask THR
plt.imshow(thr)
plt.savefig('./lena_sobel_thr.png')

# 결과 저장 - Boundary Tracing
plt.imshow(sobel_y)
plt.savefig('./lena_sobel_bt.png')


# 샘플 이미지로 네트워크 모델 생성
input = torch.FloatTensor(np.ascontiguousarray(
    np.array(Image.open('./lena.png'))[:, :, ::-1].transpose(2, 0, 1).astype(np.float32) * (1.0 / 255.0)))

# 이미지 결과값 측정
output = estimate(input)

# 결과 출력
Image.fromarray((output.clip(0.0, 1.0).np().transpose(1, 2, 0)[:, :, 0] * 255.0).astype(np.uint8)).save(
    './lena_torch.png')

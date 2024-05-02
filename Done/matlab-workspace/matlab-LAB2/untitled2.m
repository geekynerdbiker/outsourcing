clear all
 
sndfile = 'speech_female.wav';
 
[x,Fs] = audioread(sndfile);
 
N = 512;
[S,F,T] = spectrogram(x(1:Fs*1.4),N,3*N/4,N*4,Fs);
 
f = figure('Position',[500 300 700 500],'MenuBar','none', ...
  'Units','Normalized');
set(f,'PaperPosition',[0.25 1.5 8 5]);
axes('FontSize',14);
colormap('jet');
imagesc(T,F./1000,20*log10(abs(S)));
axis xy;
set(gca,'YTick',[0:2000:Fs/2]./1000,'YTickLabel',[0:2000:Fs/2]./1000);
 
ylabel('Frequency (kHz)');
xlabel('Time (s)');

print(gcf, '-depsc2', 'p2il.eps')

%%%%%%%%%%% 2.5 %%%%%%%%%%%%%%

downx=downsample(x,10);

N = 512;
[S,F,T] = spectrogram(downx(1:Fs*1.4),N,3*N/4,N*4,Fs);

f = figure('Position',[500 300 700 500],'MenuBar','none', ...
  'Units','Normalized');
set(f,'PaperPosition',[0.25 1.5 8 5]);
axes('FontSize',14);
colormap('jet');
imagesc(T,F./1000,20*log10(abs(S)));
axis xy;
set(gca,'YTick',[0:2000:Fs/2]./1000,'YTickLabel',[0:2000:Fs/2]./1000);
 
ylabel('Frequency (kHz)');
xlabel('Time (s)');
print(gcf, '-depsc2', 'dwn_p2il.eps')
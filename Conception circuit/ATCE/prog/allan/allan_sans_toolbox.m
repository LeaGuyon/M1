% Chargement du fichier
[signal, ~] = audioread('signal.wav');
Fs = 1;  % Si tu es sûre que ton signal est à 1Hz

% Si le signal est stéréo, on le convertit en mono
if size(signal,2) > 1
    signal = mean(signal, 2);
end

N = length(signal);
maxM = floor(N/2);
mList = floor(logspace(0, log10(maxM), 30));  % Valeurs de tau (logarithmiques)
mList = unique(mList);  % pour éviter les doublons
tauList = mList / Fs;
avar = zeros(size(tauList));

for i = 1:length(mList)
    m = mList(i);
    K = floor(N / m) - 1;
    if K < 1
        avar(i) = NaN;
        continue;
    end
    y = zeros(1, K);
    for k = 1:K
        idx1 = (k-1)*m + 1;
        idx2 = k*m;
        y(k) = mean(signal(idx1:idx2));
    end
    diffs = diff(y);
    avar(i) = 0.5 * mean(diffs.^2);
end

% Tracé
loglog(tauList, avar)
xlabel('\tau (s)')
ylabel('\sigma^2(\tau)')
title('Variance d''Allan (implémentation manuelle)')
grid on

%% loadLF
umax = 15;
vmax = 15;
xmax = 434;
ymax = 625;
channels = 1;
LF = zeros(umax, vmax, xmax, ymax, channels);
for i=1:umax
    for j=1:vmax
        filename = sprintf("input/%d_%d.bmp",i,j);
        image = imread(sprintf("input/%d_%d.bmp",i,j));
        if channels == 1
            image = rgb2gray(image);
        end
        LF(i,j,:,:,:) = im2double(image);
    end
end
%% interpolation Grid
[xx,yy] = ndgrid(1:xmax,1:ymax);
ucenter = ceil(umax/2);
vcenter = ceil(vmax/2);
%% single image
alpha = 1.25;

tic;
temp = zeros(xmax,ymax,channels);
for u = 1:umax
    for v = 1:vmax
        for c = 1:channels
            xq = xx + (u - ucenter) * (1 - 1/alpha);
            yq = yy + (v - vcenter) * (1 - 1/alpha);
            xq = min(max(xq,1), xmax);
            yq = min(max(yq,1), ymax);
            image = squeeze(LF(u,v,:,:,c));
            temp(:,:,c) = temp(:,:,c) + interp2(image, yq, xq, 'linear');
        end

    end
end

result = temp / (umax*vmax);
imshow(result);
title(sprintf("alpha = %.3f", alpha));
toc;
%% multiple images
tic;
for alpha = 0.5:0.1:1.5
    for u = 1:umax
        for v = 1:vmax
            for c = 1:channels
                xq = xx + (u - ucenter) * (1 - 1/alpha);
                yq = yy + (v - vcenter) * (1 - 1/alpha);
                xq = min(max(xq,1), xmax);
                yq = min(max(yq,1), ymax);
                image = squeeze(LF(u,v,:,:,c));
                temp(:,:,c) = temp(:,:,c) + interp2(image, yq, xq, 'linear');
            end

        end
    end
    imshow(result);
    title(sprintf("alpha = %.3f", alpha));    
end
toc;

